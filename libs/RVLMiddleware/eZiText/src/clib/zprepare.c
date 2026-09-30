#include <zi8clib/zitypes.h>

void Zi8Memset(ziPtr, ziU32, ziU32);
void Zi8Memcpy(ziPtr, ziPtr, ziU32);
ziBool Zi8IsComponent(ziWChar ZI_NEED_WORK);
ziU32 Zi8GetTableAddress(ziU8, ziU8 ZI_NEED_WORK);
ziU16 Zi8GetTableCount(ziU8, ziU8 ZI_NEED_WORK);
ziU8 Zi8GetPyPhonetic(ziWChar*, ziU8, ziWChar*, ziWChar*, ziU8*, ziWChar*, ziWChar* ZI_NEED_WORK);
ziU8 Zi8GetBpmfPhonetic(ziWChar*, ziU8, ziWChar*, ziWChar*, ziWChar*, ziWChar* ZI_NEED_WORK);

ziBool Zi8PrepareMatch(ziGetParam* request, ziMatchParam* match, ziU8 skipMode ZI_NEED_WORK)

{
  ziU8 masks[12];
  ziU8 strokes[12];
  ziU8* component;
  ziU8* componentIndex;
  ziU8 strokePrefix[4];
  ziU8 maskPrefix[4];
  ziU8* phoneticTable;
  ziWChar* phoneticInput;
  ziU16 element;
  ziU16 phoneticCount;
  ziU16 phoneticInitial;
  ziU16 phoneticMask;
  ziU16 phoneticCode;
  ziU16 phoneticLength;
  ziWChar initial;
  ziWChar final;
  ziWChar bestInitial;
  ziWChar bestFinal;
  ziWChar previousFinal;
  ziWChar previousInitial;
  ziU8 elementCount;
  ziU8 elementIndex;
  ziU8 stroke;
  ziU8 contextMask;
  ziU8 mode;
  ziU8 nibbles;
  ziU8 index;

  stroke = 0;
  contextMask = 0x20;
  Zi8Memset(match,0,0x1ee);
  nibbles = 0;
  elementIndex = 0;
  elementCount = request->elementCount;
  while (elementCount != 0) {
    if (request->elements[elementCount - 1] != 0xEF09) break;
    elementCount--;
  }
  match->count = elementCount;
  for (index = 0; index < elementCount; index++) {
    if (request->elements[index] != 0xEF00) {
      match->count = 0;
      break;
    }
  }
  if (elementCount != 0) {
    match->comp = element = request->elements[0];
    if (Zi8IsComponent(element,__zi8_work_data) != 0) {
      elementIndex++;
      component = (ziU8*)Zi8GetTableAddress(1,2,__zi8_work_data);
      componentIndex = (ziU8*)Zi8GetTableAddress(1,6,__zi8_work_data);
      componentIndex += (element - 0xef10) * 2;
      match->field22 = (((ziU16)componentIndex[1] & 0x3f) << 8) + *componentIndex;
      component += (ziU32)match->field22 * 8;
      switch(*component & 0xf) {
      case 0:
      case 9:
      case 10:
      default:
        break;
      case 1:
        match->comp = 0xEF00 + 4;
        break;
      case 2:
        match->comp = 0xEF00 + 1;
        break;
      case 3:
      case 0xb:
        match->comp = 0xEF00 + 7;
        break;
      case 4:
        match->comp = 0xEF00 + 6;
        break;
      case 5:
        match->comp = 0xEF00 + 3;
        break;
      case 6:
        match->comp = 0xEF00 + 5;
        break;
      case 7:
        match->comp = 0xEF00 + 8;
        break;
      case 8:
        match->comp = 0xEF00 + 2;
      }
      for (index = 0; index < (component[5] >> 1) + 1; index++) {
        if (index < 4) {
          match->arrD[index] = component[index];
          match->arr1[index] = 0xff;
        }
      }
      if ((index != 0) && ((component[5] & 1) == 0)) {
        index--;
        match->arrD[index] &= 0xf0;
        match->arr1[index] = match->arr1[index] & 0xf0;
      }
      nibbles = (ziU8)(component[5] + 1);
      if (8 < nibbles) {
        nibbles++;
      }
    }
  }
  match->arr1[0] &= 0xf;
  match->arrD[0] &= 0xf;
  if (skipMode == '\0') {
    mode = 0;
    if (((request->subLanguage & 0x80) == 0) && ((request->subLanguage & 0x40) == 0)) {
      if ((request->subLanguage & 8) == 0) {
        if (((request->subLanguage & 0x20) != 0) || ((request->subLanguage & 0x10) != 0)) {
          mode = 2;
        }
      }
      else {
        mode = 4;
      }
    }
    else {
      mode = 1;
    }
    if (mode == 0) {
      mode = request->subLanguage;
    }
    switch (mode) {
    case 1:
    case 2:
    case 4:
        match->arr1[0] |= (ziU8)(mode << 4);
        match->arrD[0] |= (ziU8)(mode << 4);
        break;
    }
  }
  if (nibbles == 0) {
    nibbles = 1;
  }
  if (((request->getMode == '\0') || (request->getMode == '\x10')) ||
     (request->getMode == '\x05')) {
    Zi8Memcpy(masks,match->arr1,0xc);
    Zi8Memcpy(strokes,match->arrD,0xc);
    do {
      while (elementIndex < elementCount) {
        element = request->elements[elementIndex++];
        switch (element) {
        case 0xef02: stroke = 0; break;
        case 0xef04: stroke = 1; break;
        case 0xef01: stroke = 2; break;
        case 0xef07: stroke = 3; break;
        case 0xef06: stroke = 4; break;
        case 0xef03: stroke = 5; break;
        case 0xef05: stroke = 6; break;
        case 0xef08: stroke = 7; break;
        case 0xef0b: stroke = 8; break;
        case 0xef0a: stroke = 4; break;
        case 0xf360: stroke = 0xff; break;
        default: stroke = 0; break;
        }
        if (stroke == 0xff) break;
        if (0x17 < nibbles) {
          match->length = 0x18;
          return 0;
        }
        if (nibbles == 8) {
          nibbles++;
        }
        if ((nibbles & 1) != 0) {
          strokes[nibbles >> 1] = strokes[nibbles >> 1] | stroke;
          if (element == 0xef0b) {
            masks[nibbles >> 1] = masks[nibbles >> 1] | 8;
          }
          else if (element == 0xef0a) {
            masks[nibbles >> 1] = masks[nibbles >> 1] | 4;
          }
          else if (element != 0xef00) {
            masks[nibbles >> 1] = masks[nibbles >> 1] | 7;
          }
                } else {
          strokes[nibbles >> 1] = strokes[nibbles >> 1] | (ziU8)(stroke << 4);
          if (element == 0xef0b) {
            masks[nibbles >> 1] = masks[nibbles >> 1] | 0x80;
          }
          else if (element == 0xef0a) {
            masks[nibbles >> 1] = masks[nibbles >> 1] | 0x40;
          }
          else if (element != 0xef00) {
            masks[nibbles >> 1] = masks[nibbles >> 1] | 0x70;
          }
                }
        nibbles++;
      }
      for (index = 0; index < 4; index++) {
        maskPrefix[index] = masks[index];
        strokePrefix[index] = strokes[index];
      }
      if ((1 < nibbles) && (nibbles < 8)) {
        if ((nibbles & 1) == 0) {
          maskPrefix[nibbles >> 1] = maskPrefix[nibbles >> 1] | 0xf0;
          strokePrefix[nibbles >> 1] = strokePrefix[nibbles >> 1] | 0xf0;
        }
        else {
          maskPrefix[nibbles >> 1] = maskPrefix[nibbles >> 1] | 0xf;
          strokePrefix[nibbles >> 1] = strokePrefix[nibbles >> 1] | 0xf;
        }
      }
      if (match->nSeg == 0) {
        Zi8Memcpy(match->arr1,masks,0xc);
        Zi8Memcpy(match->arrD,strokes,0xc);
        Zi8Memcpy(match->arr19,maskPrefix,4);
        Zi8Memcpy(match->arr1D,strokePrefix,4);
        match->length = nibbles;
      }
      Zi8Memcpy(match->segs1 + match->nSeg * 12,masks,0xc);
      Zi8Memcpy(match->segsD + match->nSeg * 12,strokes,0xc);
      match->nSeg++;
      if (((stroke != 0xff) || (elementCount <= elementIndex)) || (0xf < match->nSeg)) goto complete;
      Zi8Memset(masks,0,0xc);
      Zi8Memset(strokes,0,0xc);
      masks[0] = match->arr1[0] & 0xf0;
      strokes[0] = match->arrD[0] & 0xf0;
      nibbles = 1;
    } while (1);
  }
  match->length = nibbles;
  if (elementCount != 0) {
    if ((request->getMode == '\x01') || (request->getMode == '\f')) {
      phoneticTable = (ziU8*)Zi8GetTableAddress(1,3,__zi8_work_data);
      phoneticCount = Zi8GetTableCount(1,3,__zi8_work_data);
    }
    else {
      phoneticTable = (ziU8*)Zi8GetTableAddress(1,4,__zi8_work_data);
      phoneticCount = Zi8GetTableCount(1,4,__zi8_work_data);
    }
    if ((request->getMode == '\x01') || (request->getMode == '\f')) {
      match->nCand = Zi8GetPyPhonetic(request->elements,elementCount,match->phon,match->phon2,
                                    &request->count,&match->first,&match->first2,__zi8_work_data);
    }
    else {
      initial = 0;
      final = 0;
      bestInitial = 0;
      bestFinal = 0;
      previousInitial = 0;
      previousFinal = 0;
      phoneticInput = request->elements;
      match->nCand = 0;
      request->count = request->elementCount;
      phoneticLength = 1;
      for (index = 0; index < elementCount; index++) {
        if (Zi8GetBpmfPhonetic(phoneticInput,phoneticLength & 0xff,&initial,&final,&bestInitial,&bestFinal,
                              __zi8_work_data) == 0) {
          if ((index == 0) ||
             ((((1 < phoneticLength && (phoneticInput[phoneticLength - 2] == 0xF360)) &&
               (phoneticInput[phoneticLength - 1] == 0xF360)) ||
              (++match->nCand == 0x10)))) {
            initial = 0xffff;
            final = 0xffff;
            bestInitial = 0xffff;
            bestFinal = 0xffff;
            match->nCand = 0;
            break;
          }
          if (phoneticInput[phoneticLength - 1] == 0xF360) {
            match->nCand--;
            bestInitial = previousInitial;
            bestFinal = previousFinal;
            final = bestFinal;
            initial = bestInitial;
            goto savePhonetic;
          }
          if (match->nCand == 1) {
            request->count = (ziS8)phoneticLength + -1;
          }
          phoneticInput = phoneticInput + phoneticLength - 1;
          phoneticLength = 0;
          index--;
        }
        else {
savePhonetic:
          match->phon[match->nCand] = initial;
          match->phon2[match->nCand] = final;
          previousFinal = bestFinal;
          previousInitial = bestInitial;
          if (match->nCand == 0) {
            match->first = bestInitial;
            match->first2 = bestFinal;
          }
        }
        phoneticLength++;
      }
      if (elementCount != 0) {
        match->phon[match->nCand] = initial;
        match->phon2[match->nCand] = final;
        if (match->nCand == 0) {
          match->first = bestInitial;
          match->first2 = bestFinal;
        }
        match->nCand++;
      }
    }
    if (((request->context & contextMask) != 0) &&
       ((1 < match->nCand || (request->count != elementCount)))) {
      match->phon[0] = 0xFFFF;
      match->phon2[0] = 0xFFFF;
      match->nCand = 0;
    }
    if (((request->getOptions & 0x20) == 0) &&
       ((match->phon[0] != 0xFFFF || (match->phon2[0] != 0xFFFF)))) {
      if (match->nCand < 2) {
        phoneticInitial = match->phon[0];
        phoneticMask = match->phon2[0];
      }
      else {
        phoneticInitial = match->phon[match->nCand - 1];
        phoneticMask = match->phon2[match->nCand - 1];
      }
      phoneticInitial = phoneticInitial & 0xfff8;
      phoneticMask = phoneticMask & 0xfff8;
      phoneticLength = 0;
      while ((phoneticLength < phoneticCount &&
             (phoneticCode = (phoneticTable[phoneticLength * 2 + 1] << 8) | phoneticTable[phoneticLength * 2],
             phoneticMask != (phoneticCode & phoneticInitial)))) {
        phoneticLength++;
      }
      if (phoneticLength == phoneticCount) {
        match->phon[0] = 0xFFFF;
        match->phon2[0] = 0xFFFF;
      }
    }
  }
complete:
  return 1;
}
