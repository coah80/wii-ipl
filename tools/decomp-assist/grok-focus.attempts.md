# grok-focus is_url_ext

Replaced the eight DECOMP_FORCE_ACTIVE wide strings with focus_object::is_url_ext.
The function is not in the target object (linker must strip it). Strings stay in source order.

Attempt 1: local `const wchar_t* exts[] = { L".html", ... }` loop.
- .rodata 176 -> 208 (MWCC emitted the pointer table). Restored.

Attempt 2: unrolled wcsncmp tail checks, one local pointer per extension.
- .data/.rodata/.sdata/.sdata2 identical to the force-active object
- 89/89 original functions byte-identical, odiff differing 0

Attempt 3: same compares in a loop, pointers assigned one by one (no aggregate initializer).
- .data sha 672d08c07636 matches the force-active build (2164 bytes; orig object is 2168 with 4 trailing zero bytes, unchanged)
- .rodata/.sdata/.sdata2 identical to the original object
- pool IDENTICAL 80/80
- odiff: 89/89 differing 0
- no DECOMP_FORCE_ACTIVE left in iplFocusObject.cpp
