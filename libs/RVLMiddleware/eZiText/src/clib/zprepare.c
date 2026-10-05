#include <zi8clib/zitypes.h>

void Zi8Memset(ziPtr, ziU32, ziU32);
void Zi8Memcpy(ziPtr, ziPtr, ziU32);
ziBool Zi8IsComponent(ziWChar ZI_NEED_WORK);
ziU32 Zi8GetTableAddress(ziU8, ziU8 ZI_NEED_WORK);
ziU16 Zi8GetTableCount(ziU8, ziU8 ZI_NEED_WORK);
ziU8 Zi8GetPyPhonetic(ziWChar*, ziU8, ziWChar*, ziWChar*, ziU8*, ziWChar*, ziWChar* ZI_NEED_WORK);
ziU8 Zi8GetBpmfPhonetic(ziWChar*, ziU8, ziWChar*, ziWChar*, ziWChar*, ziWChar* ZI_NEED_WORK);

ziBool Zi8PrepareMatch(ziGetParam* request, ziMatchParam* match, ziU8 skipMode ZI_NEED_WORK) {
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
  ziWChar previousInitial;
  ziWChar previousFinal;
  ziBool hasComponent;
  ziU8 elementCount;
  ziU8 elementIndex;
  ziU8 stroke;
  ziU8 contextMask;
  ziU8 mode;
  ziU8 savedNibbles;
  struct {
    ziWChar* phoneticInput;
    ziU8* phoneticTable;
    ziU8 strokePrefix[4];
    ziU8 maskPrefix[4];
    ziU8* componentIndex;
    ziU8* component;
    ziU8 strokes[12];
    ziU8 masks[12];
  } buffers;
  ziU8 nibbles;
  ziU8 index;

  stroke = 0;
  contextMask = 0x20;
  Zi8Memset(match,0,0x1ee);
  hasComponent = 0;
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
    element = request->elements[0];
    match->comp = element;
    if (Zi8IsComponent(element,__zi8_work_data) != 0) {
      elementIndex++;
      hasComponent = 1;
      buffers.component = (ziU8*)Zi8GetTableAddress(1,2,__zi8_work_data);
      buffers.componentIndex = (ziU8*)Zi8GetTableAddress(1,6,__zi8_work_data);
      buffers.componentIndex += (element - 0xef10) * 2;
      match->componentIndex = ((buffers.componentIndex[1] & 0x3f) << 8) + *buffers.componentIndex;
      buffers.component += (ziU32)match->componentIndex * 8;
      switch(*buffers.component & 0xf) {
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
      for (index = 0; index < (buffers.component[5] >> 1) + 1; index++) {
        if (index < 4) {
          match->recordValues[index] = buffers.component[index];
          match->recordMasks[index] = 0xff;
        }
      }
      if ((index != 0) && ((buffers.component[5] & 1) == 0)) {
        index--;
        match->recordValues[index] &= 0xf0;
        match->recordMasks[index] &= 0xf0;
      }
      nibbles = (ziU8)(buffers.component[5] + 1);
      if (8 < nibbles) {
        nibbles++;
      }
    }
  }
  match->recordMasks[0] &= 0xf;
  match->recordValues[0] &= 0xf;
  if (skipMode == '\0') {
    mode = 0;
    if ((request->subLanguage & 0x80) != 0 || (request->subLanguage & 0x40) != 0) {
      mode = 1;
    } else if ((request->subLanguage & 8) != 0) {
      mode = 4;
    } else if ((request->subLanguage & 0x20) != 0 || (request->subLanguage & 0x10) != 0) {
      mode = 2;
    }
    if (mode == 0) {
      mode = request->subLanguage;
    }
    switch (mode) {
    case 1:
    case 2:
    case 4:
      match->recordMasks[0] |= (ziU8)(mode << 4);
      match->recordValues[0] |= (ziU8)(mode << 4);
      break;
    }
  }
  if (nibbles == 0) {
    nibbles = 1;
  }
  if (((request->getMode == '\0') || (request->getMode == '\x10')) ||
    (request->getMode == '\x05')) {
    Zi8Memcpy(buffers.masks,match->recordMasks,0xc);
    Zi8Memcpy(buffers.strokes,match->recordValues,0xc);
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
          buffers.strokes[nibbles >> 1] |= stroke;
          if (element == 0xef0b) {
            buffers.masks[nibbles >> 1] |= 8;
          }
          else if (element == 0xef0a) {
            buffers.masks[nibbles >> 1] |= 4;
          }
          else if (element != 0xef00) {
            buffers.masks[nibbles >> 1] |= 7;
          }
        } else {
          buffers.strokes[nibbles >> 1] |= stroke << 4;
          if (element == 0xef0b) {
            buffers.masks[nibbles >> 1] |= 0x80;
          }
          else if (element == 0xef0a) {
            buffers.masks[nibbles >> 1] |= 0x40;
          }
          else if (element != 0xef00) {
            buffers.masks[nibbles >> 1] |= 0x70;
          }
        }
        nibbles++;
      }
      savedNibbles = nibbles;
      for (index = 0; index < 4; index++) {
        buffers.maskPrefix[index] = buffers.masks[index];
        buffers.strokePrefix[index] = buffers.strokes[index];
      }
      if ((1 < nibbles) && (nibbles < 8)) {
        index = nibbles >> 1;
        if ((nibbles & 1) != 0) {
          buffers.maskPrefix[index] = buffers.maskPrefix[index] | 0xf;
          buffers.strokePrefix[index] = buffers.strokePrefix[index] | 0xf;
        } else {
          buffers.maskPrefix[index] = buffers.maskPrefix[index] | 0xf0;
          buffers.strokePrefix[index] = buffers.strokePrefix[index] | 0xf0;
        }
      }
      if (match->nSeg == 0) {
        Zi8Memcpy(match->recordMasks,buffers.masks,0xc);
        Zi8Memcpy(match->recordValues,buffers.strokes,0xc);
        Zi8Memcpy(match->prefixMasks,buffers.maskPrefix,4);
        Zi8Memcpy(match->prefixValues,buffers.strokePrefix,4);
        match->length = savedNibbles;
      }
      Zi8Memcpy((ziU8 (*)[12])match->segmentMasks + match->nSeg,buffers.masks,0xc);
      Zi8Memcpy((ziU8 (*)[12])match->segmentValues + match->nSeg,buffers.strokes,0xc);
      match->nSeg++;
      if (stroke != 0xff || elementIndex >= elementCount || match->nSeg >= 0x10) break;
      Zi8Memset(buffers.masks,0,0xc);
      Zi8Memset(buffers.strokes,0,0xc);
      buffers.masks[0] = match->recordMasks[0] & 0xf0;
      buffers.strokes[0] = match->recordValues[0] & 0xf0;
      nibbles = 1;
    } while (1);
    return 1;
  }
  match->length = nibbles;
  if (elementCount != 0) {
    if ((request->getMode == '\x01') || (request->getMode == '\f')) {
      buffers.phoneticTable = (ziU8*)Zi8GetTableAddress(1,3,__zi8_work_data);
      phoneticCount = Zi8GetTableCount(1,3,__zi8_work_data);
    }
    else {
      buffers.phoneticTable = (ziU8*)Zi8GetTableAddress(1,4,__zi8_work_data);
      phoneticCount = Zi8GetTableCount(1,4,__zi8_work_data);
    }
    if ((request->getMode == '\x01') || (request->getMode == '\f')) {
      match->nCand = Zi8GetPyPhonetic(request->elements,elementCount,match->phon,match->phon2,
        &request->completion,&match->first,&match->first2,__zi8_work_data);
    }
    else {
      initial = 0;
      final = 0;
      bestFinal = bestInitial = 0;
      previousFinal = previousInitial = 0;
      buffers.phoneticInput = request->elements;
      match->nCand = 0;
      request->completion = request->elementCount;
      phoneticLength = 1;
      for (index = 0; index < elementCount;) {
        stroke = Zi8GetBpmfPhonetic(buffers.phoneticInput,phoneticLength,&initial,&final,&bestInitial,&bestFinal,
          __zi8_work_data);
        if (stroke != 0) {
          previousInitial = bestInitial;
          previousFinal = bestFinal;
savePhonetic:
          match->phon[match->nCand] = initial;
          match->phon2[match->nCand] = final;
          if (match->nCand == 0) {
            match->first = bestInitial;
            match->first2 = bestFinal;
          }
        }
        else {
          if ((index == 0) ||
            ((((1 < phoneticLength && (buffers.phoneticInput[phoneticLength - 2] == 0xF360)) &&
            (buffers.phoneticInput[phoneticLength - 1] == 0xF360)) ||
            (++match->nCand == 0x10)))) {
            initial = 0xffff;
            final = 0xffff;
            bestInitial = 0xffff;
            bestFinal = 0xffff;
            match->nCand = 0;
            break;
          }
          if (buffers.phoneticInput[phoneticLength - 1] == 0xF360) {
            match->nCand--;
            bestInitial = initial = previousInitial;
            bestFinal = final = previousFinal;
            goto savePhonetic;
          }
          if (match->nCand == 1) {
            request->completion = phoneticLength - 1;
          }
          buffers.phoneticInput = buffers.phoneticInput + phoneticLength - 1;
          phoneticLength = 0;
          index--;
        }
        index++;
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
      ((1 < match->nCand || (request->completion != elementCount)))) {
      match->phon[0] = 0xFFFF;
      match->phon2[0] = 0xFFFF;
      match->nCand = 0;
    }
    if (((request->getOptions & 0x20) == 0) &&
      ((match->phon[0] != 0xFFFF || (match->phon2[0] != 0xFFFF)))) {
      if (match->nCand > 1) {
        phoneticInitial = match->phon[match->nCand - 1] & 0xfff8;
        phoneticMask = match->phon2[match->nCand - 1] & 0xfff8;
      }
      else {
        phoneticInitial = match->phon[0] & 0xfff8;
        phoneticMask = match->phon2[0] & 0xfff8;
      }
      for (phoneticLength = 0; phoneticLength < phoneticCount; phoneticLength++) {
        phoneticCode = buffers.phoneticTable[phoneticLength * 2] | ((ziU16)buffers.phoneticTable[phoneticLength * 2 + 1] << 8);
        if (phoneticMask == (phoneticCode & phoneticInitial)) break;
      }
      if (phoneticLength == phoneticCount) {
        match->phon[0] = 0xFFFF;
        match->phon2[0] = 0xFFFF;
      }
    }
  }
  return 1;
}
