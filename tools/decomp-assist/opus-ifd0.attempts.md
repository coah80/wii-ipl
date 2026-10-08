# opus-ifd0: exif_parse IFD0/IFD1 switch layout

Unit `libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse`. Start: IFD0 457 differing
(0x780 vs 0x784), IFD1 226 differing (0x3bc vs 0x3c8). End: both 0 differing,
all six functions exact, pool identical, unit flipped to Matching, DOL SHA1
26116613f624061ba99c8d1a299aaa6efa85670d.

## Switch-tree model (scratch compiles of a bare `switch` in /tmp)

MWCC builds the binary tree over sorted ranges: case ranges, with the gaps
between them going to default. A run of consecutive values with the same
label becomes one range, and so does a case whose label equals the default
label when it sits next to a gap. A leaf `cmp v; beq; <lo>; <hi>` collapses to
a single `b default` only when both sides are pure gaps. Target IFD0's
`beqlr; bltlr; blr` at 0x103 means the (0x103,0x111) side holds a case range
that carries the default label, so it does not collapse.

| # | change | IFD0 result |
|---|--------|-------------|
| 1 | extra case at 0x0..0x105 with break/return/default | tree reshuffles |
| 2 | `case 0x10f/0x110` sharing `default: return;` | tree matches |
| 3 | same plus JPEG_INTERCHANGE* kept in the break group | extra `cmp 0x203` (0x201/0x202 no longer default label) |
| 4 | move JPEG_INTERCHANGE* into the default group | tree exact, one extra trailing blr (482) |
| 5 | default group first / last, break vs return, ignored group return | always 482: a `return` block costs its own blr |
| 6 | 48 combinations of group body/position/PIXEL_Y exit/default | all 481+1 or worse |
| 7 | PIXEL_Y falls through into the trailing `default: return;` group | 481/481, 26 differing (registers only) |
| 8 | rx57 register fix (offsetRaw/numeratorRaw + convertExifWord, named denominator base) | **0 differing** |
| 9 | tidier out-param `readExifU32` helper instead of #8 | 30/48 differing, rejected |

## IFD1

Target tree: 0x111 has a label distinct from default, while 0x112 and 0x11c merge
into the gaps after them. A scratch search over break/return groups, default
placement and Make/Model found an exact tree with STRIP_OFFSETS alone in its
own group, the rest plus MAKE/MODEL/default in another, and PLANAR_CONFIGURATION
left to default. In the real file the same fall-through layout as IFD0 (break
group first, `default: return;` group last, JPEG_INTERCHANGE_FORMAT_LENGTH falling
into it) plus the rx57 register fix gives 0 / 242. The mirrored layout (STRIP
return last) is also exact.

Behaviour is unchanged: every added or moved tag still does nothing, and each
fall-through runs into a bare `return`.
