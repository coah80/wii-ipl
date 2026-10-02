#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>
#include <zi8clib/zconvert.h>

ziU32 Zi8GetTableSize(ziU8 language, ziU8 table, ziPtr work);
ziU32 Zi8GetTableAddress(ziU8 language, ziU8 table, ziPtr work);
ziU16 Zi8GetTableCount(ziU8 language, ziU8 table, ziPtr work);
ziU8* ZiDAWGGetGraph(zi8DawgCtx* context);
ziU8* ZiDAWGGetGraphInfo(zi8DawgCtx* context, ziU8* table, ziS16* keys);
ziU32 ZiDAWGgetCHARattribute(zi8DawgCtx* context, ziU8* graph, ziPtr work);
ziU8 ZiDAWGgetEOWattribute(ziU8* graph);
ziU8* ZiDAWGGetChild(ziU8* graph);
ziU8* ZiDAWGGetSibling(ziU8* graph);

ziU32 Zi8MatchROMdata0(ziWChar* elements, ziU8 count, ziU8 language,
                      ziWChar* output, ziU16 capacity, ziU8 mode, ziU8 status,
                      ziU8 graphTable, ziU8 keyTable, ziU8 acceptPrefix,
                      ziU8* prefixLength, zi8DawgCtx* context, ziU8* search,
                      ziPtr __zi8_work_data) {
    ziU8 result = 0;
    ziU8* graphData;
    ziU8* keyData;
    ziS32 keyCount;
    ziS32 convertedKey;
    ziU16 searching;
    ziU16 key;
    ziU16 keys[3];
    ziU16 index;
    zi8DawgRec* current;
    zi8DawgRec* records = context->recs;

    if (language != context->lang || graphTable != context->key) records[0].key = 0;
    if (count == 1 && mode != 0 && graphTable == 0xe) goto finish_graph;
    if (status != 0) {
        if (records[context->cnt - 1].node == (ziU8*)context->unk_0x338) goto finish_graph;
        for (index = 0; index < count; index++) {
            if (records[index].key != elements[index] &&
                (ziU16)records[index].attr != elements[index]) goto finish_graph;
        }
        if (mode == 1) acceptPrefix = 0;
    } else {
        if (ZI_WORK->unk_0x141E != 0 && graphTable == 0xc &&
            Zi8GetTableSize(language, ZI_WORK->unk_0x141E, ZI_WORK) != 0) {
            graphData = (ziU8*)Zi8GetTableAddress(language, ZI_WORK->unk_0x141E, ZI_WORK);
            keyTable = ZI_WORK->unk_0x141E + 1;
        } else {
            if (Zi8GetTableSize(language, graphTable, ZI_WORK) == 0) {
                Zi8LogError(0x961, ZI_WORK);
                goto finish_graph;
            }
            graphData = (ziU8*)Zi8GetTableAddress(language, graphTable, ZI_WORK);
        }
        context->table = graphData;
        context->cap = (((ziU16)context->table[2] << 8) + context->table[3]) / 3;
        context->p08 = context->table + 4;
        context->p0C = context->table + context->cap * 2 + 4;
        context->lang = language;
        context->key = graphTable;
        index = 0;
        while (index < count && records[index].key == elements[index]) index++;
        if (index >= 2) {
            records[0].node = records[index - 1].back;
        } else {
            key = Zi8GetTableSize(language, keyTable, ZI_WORK);
            if (key != 0 && ZI_WORK->userKeys[language] == 0) {
                index = 0;
                goto check_keys;
next_key:
                {
                    keys[index] = Zi8ConvertWC2Key(elements[index], language, ZI_WORK);
                    if (keys[index] == 0) keys[index] = elements[index];
                    index++;
                }
check_keys:
                if (count < 2) keyCount = count;
                else keyCount = 2;
                if (index < keyCount) goto next_key;
                keys[index] = 0;
                keyData = (ziU8*)Zi8GetTableAddress(language, keyTable, ZI_WORK);
                context->p14 = keyData + 2;
                keyData += context->cap * 2 + 2;
                records[0].node = ZiDAWGGetGraphInfo(context, keyData, (ziS16*)keys);
            } else {
                records[0].node = ZiDAWGGetGraph(context);
                context->unk_0x338 = 0;
                context->p14 = 0;
            }
            records[0].key = 0;
            if (records[0].node == (ziU8*)0) goto finish_graph;
        }
        context->cnt = 1;
        search[1] = count;
        search[0] = 0;
        if (mode == 1) {
            search[0] = 1;
            acceptPrefix = 0;
        } else if (mode == 0 && acceptPrefix == 0) search[1]++;
    }
    searching = 1;
    current = &records[context->cnt - 1];
    while (searching && context->cnt != 0 && current->node != (ziU8*)context->unk_0x338) {
        if (capacity < context->cnt) goto finish_graph;
        current->attr = ZiDAWGgetCHARattribute(context, current->node, ZI_WORK);
        if (context->cnt <= count) {
            if (context->p14 == 0) {
                convertedKey = Zi8ConvertWC2Key((ziU16)current->attr, language, ZI_WORK);
            } else {
                convertedKey = ((ziU16)context->p14[(current->attr >> 24) * 2] << 8) +
                               (context->p14 + (current->attr >> 24) * 2)[1];
            }
            key = convertedKey;
            if (key != elements[context->cnt - 1] &&
                (ziU16)current->attr != elements[context->cnt - 1]) goto next_sibling;
            if (current->key != elements[context->cnt - 1]) {
                current->key = elements[context->cnt - 1];
                current->back = records[0].node;
                records[context->cnt].key = 0;
            }
            if (prefixLength != 0 && *prefixLength < context->cnt &&
                ZiDAWGgetEOWattribute(current->node) != 0) {
                *prefixLength = context->cnt;
                for (index = 0; index < context->cnt; index++) output[index] = (ziU16)records[index].attr;
            }
            if (context->cnt < count) goto descend;
        }
        if (context->cnt < search[1]) goto descend;
        if (search[0] != 0 && context->cnt > search[1]) goto next_sibling;
        if (acceptPrefix != 0 || ZiDAWGgetEOWattribute(current->node) != 0) {
            for (index = 0; index < context->cnt; index++) output[index] = (ziU16)records[index].attr;
            result = context->cnt;
            searching = 0;
            if (acceptPrefix != 0) goto next_sibling;
        }
        if (search[0] != 0 && context->cnt >= search[1]) goto next_sibling;
descend:
        records[context->cnt].node = ZiDAWGGetChild(records[context->cnt - 1].node);
        if (records[context->cnt].node == (ziU8*)0) goto next_sibling;
        context->cnt++;
        if (ZI_WORK->maxCnt < context->cnt) ZI_WORK->maxCnt = context->cnt;
        goto update_current;
next_sibling:
        while (context->cnt != 0) {
            records[context->cnt - 1].node = ZiDAWGGetSibling(records[context->cnt - 1].node);
            if (records[context->cnt - 1].node != (ziU8*)0) break;
            context->cnt--;
        }
update_current:
        current = &records[context->cnt - 1];
    }
finish_graph:
    return result;
}
ziU8* NextDawgGroup(ziU8* group, ziU8 language, ziPtr __zi8_work_data)
{
  if (Zi8GetTableSize(language,0x1c,ZI_WORK) != 0) {
    if (group == 0) {
      group = (ziU8*)Zi8GetTableAddress(language,0x1c,ZI_WORK);
      if (group == 0) {
        Zi8LogError(0x962,ZI_WORK);
        return 0;
      }
      if (ZI_WORK->unk_0x141D == 0) {
        return group;
      }
    }
    while (group[0] != 0xff || group[1] != 0xff) {
      group = group + 1;
    }
    group = group + 2;
    if (group[0] == 0xff) {
      Zi8LogError(0x963,ZI_WORK);
      return 0;
    }
    return group;
  }
  Zi8LogError(0x961,ZI_WORK);
  return 0;
}

unsigned int Zi8MatchROMdata1(ziWChar *elements, ziU8 count, ziU8 language, ziWChar *output, ziU16 capacity, ziU8 mode, ziU8 status, ziU32 groupIndex, char *group, ziU8 acceptPrefix, ziPtr __zi8_work_data)
{
  unsigned int result;
  ziU32 tableAddress;

  result = 0;
  if (status == 0) {
    ZI_WORK->groupPtr = (ziU8*)group;
    if (ZI_WORK->groupPtr == 0) {
      if (Zi8GetTableSize(language & 0xff,0xb,ZI_WORK) != 0) {
        ZI_WORK->groupPtr = (ziU8*)(tableAddress = Zi8GetTableAddress(language & 0xff,0xb,ZI_WORK));
      }
    }
    if (ZI_WORK->groupPtr != 0) {
      for (; (*ZI_WORK->groupPtr != 0xff && ((groupIndex & 0xff) != 0));
          groupIndex = groupIndex - 1) {
        while (*ZI_WORK->groupPtr != 0xff) {
          ZI_WORK->groupPtr += 2;
        }
        ZI_WORK->groupPtr++;
      }
    }
  }
  if (ZI_WORK->groupPtr == 0) {
    result = Zi8MatchROMdata0(elements,count,language & 0xff,output,capacity & 0xffff,
                             mode & 0xff,status & 0xff,0,1,acceptPrefix,0,&ZI_WORK->dawgCtx,
                             ZI_WORK->unk_0x1760,ZI_WORK);
  }
  else {
    while (*ZI_WORK->groupPtr != 0xff) {
      result = Zi8MatchROMdata0(elements,count,language & 0xff,output,
                               capacity & 0xffff,mode & 0xff,status & 0xff,
                               *ZI_WORK->groupPtr,
                               ZI_WORK->groupPtr[1],acceptPrefix,0,
                               &ZI_WORK->dawgCtx,ZI_WORK->unk_0x1760,ZI_WORK);
      if ((result & 0xff) != 0) break;
      ZI_WORK->groupPtr += 2;
      status = 0;
    }
  }
  return result;
}

unsigned int Zi8MatchROMdata2(ziWChar* elements, ziU8 count, ziU8 language,
                            ziWChar* output, ziU16 capacity, ziU8 mode,
                            ziU8 status, ziU8 reservedMode, ziU8* group,
                            ziU8 acceptPrefix, ziPtr __zi8_work_data) {
    unsigned int result = 0;
    ziU8 index;

    if (reservedMode != 0) return 0;
    if (status == 0) {
        ZI_WORK->unk_0x1768 = 0;
        ZI_WORK->matchOffset = 0;
        if (group != 0 && *group == 0xc && language == 10 && ZI_WORK->unk_0x141C != 0) {
            ZI_WORK->unk_0x141E = 0x10;
        } else {
            ZI_WORK->unk_0x141E = 0;
        }
    }
search_segment:
    ZI_WORK->maxCnt = 1;
    result = Zi8MatchROMdata1(elements + ZI_WORK->matchOffset,
                             count - ZI_WORK->matchOffset, language,
                             &ZI_WORK->unk_0x17F4[ZI_WORK->matchOffset], capacity,
                             mode, status, ZI_WORK->unk_0x1768, (char*)group,
                             acceptPrefix, ZI_WORK);
    if ((ziU8)result != 0) {
        for (index = (ziU8)(ZI_WORK->matchOffset + result); index != 0; index--) {
            output[index - 1] = ZI_WORK->unk_0x17F4[index - 1];
        }
        result = (ziU8)(result + ZI_WORK->matchOffset);
    } else {
        if (status != 0 || count == 1) goto finish_segments;
        if (mode == 1 && ZI_WORK->unk_0x1768 == 0 &&
            (ziU8)Zi8MatchROMdata1(elements + ZI_WORK->matchOffset,
                                  count - ZI_WORK->matchOffset, language,
                                  &ZI_WORK->unk_0x17F4[ZI_WORK->matchOffset], capacity,
                                  0, status, ZI_WORK->unk_0x1768, (char*)group,
                                  acceptPrefix, ZI_WORK) != 0) goto finish_segments;
        if ((Zi8GetTableCount(language, 0x1f, ZI_WORK) & 4) == 0) {
            for (index = 0; index < count; index++) {
                if (elements[index] == 0xeff1) goto finish_segments;
            }
        }
        if (ZI_WORK->maxCnt > capacity) goto finish_segments;
        for (index = ZI_WORK->maxCnt; index != 0; index--) {
            result = Zi8MatchROMdata1(elements + ZI_WORK->matchOffset, index, language,
                                     &ZI_WORK->unk_0x17F4[ZI_WORK->matchOffset], capacity,
                                     1, 0, ZI_WORK->unk_0x1768, (char*)group,
                                     acceptPrefix, ZI_WORK);
            if ((ziU8)result != 0) {
                ZI_WORK->matchOffset += (ziU8)result;
                if (ZI_WORK->matchOffset == count) return 0;
                ZI_WORK->unk_0x1768++;
                status = 0;
                ZI_WORK->unk_0x141E = 0;
                if (ZI_WORK->dawgCtx.key == 0 && language == 10) {
                    for (index = 0; index < ZI_WORK->matchOffset; index++) {
                        switch (ZI_WORK->unk_0x17F4[index]) {
                        case 0x61:
                        case 0x6f:
                        case 0x75:
                            ZI_WORK->unk_0x141E = 0x10;
                            goto search_segment;
                        }
                    }
                }
                goto search_segment;
            }
        }
    }
finish_segments:
    return result;
}

ziU32 Zi8MatchROMdata(ziWChar* elements, ziU8 count, ziU8 language,
                      ziWChar* output, ziU16 capacity, ziU8 mode, ziU8 status,
                      ziU8 reservedMode, ziU8 acceptPrefix, ziPtr __zi8_work_data) {
    ziU32 result = 0;
    ziS32 tableSize = 0;

    if (capacity < count) {
        Zi8LogError(0x321, ZI_WORK);
    } else if (status == 2) {
        Zi8LogError(100, ZI_WORK);
    } else {
        if (status == 0) {
            ZI_WORK->unk_0x17EC = 0;
            ZI_WORK->dawgGroup = NextDawgGroup(0, language, ZI_WORK);
        } else if (ZI_WORK->unk_0x17EC != 0) {
            Zi8LogError(100, ZI_WORK);
            goto finish_match;
        }
        tableSize = Zi8GetTableSize(language, 0x1c, ZI_WORK);
        if (tableSize == 0) {
            result = Zi8MatchROMdata2(elements, count, language, output, capacity,
                                     mode, status, reservedMode, 0, acceptPrefix, ZI_WORK);
        } else {
            while (ZI_WORK->dawgGroup != 0) {
                result = Zi8MatchROMdata2(elements, count, language, output, capacity,
                                         mode, status, reservedMode, ZI_WORK->dawgGroup,
                                         acceptPrefix, ZI_WORK);
                if ((ziU8)result != 0) break;
                status = 0;
                if (count <= 1 && language == 0x36) break;
                ZI_WORK->dawgGroup = NextDawgGroup(ZI_WORK->dawgGroup, language, ZI_WORK);
            }
        }
        if ((ziU8)result == 0 && status == 0 && mode == 1 && count == 1 && capacity >= 1) {
            mode = 0;
            ZI_WORK->unk_0x17EC = 1;
            if (tableSize != 0) {
                ZI_WORK->dawgGroup = NextDawgGroup(0, language, ZI_WORK);
                while (ZI_WORK->dawgGroup != 0) {
                    if ((ziU8)Zi8MatchROMdata2(elements, count, language, output, capacity,
                                              mode, status, reservedMode, ZI_WORK->dawgGroup,
                                              acceptPrefix, ZI_WORK) != 0) {
                        *output = *elements;
                        result = 1;
                        break;
                    }
                    ZI_WORK->dawgGroup = NextDawgGroup(ZI_WORK->dawgGroup, language, ZI_WORK);
                }
            } else {
                if ((ziU8)Zi8MatchROMdata2(elements, count, language, output, capacity,
                                          mode, status, reservedMode, 0, acceptPrefix, ZI_WORK) != 0) {
                    *output = *elements;
                    result = 1;
                }
            }
        }
        Zi8LogError(100, ZI_WORK);
    }
finish_match:
    return result;
}

void Zi8SyllablesROMdata(ziWChar *elements, ziU8 count, ziU8 language, ziWChar *output, ziU16 capacity, ziU8 status, ziU8* prefixLength, ziU8 reverseOrder, ziPtr __zi8_work_data)
{
  ziU32 keyTable;
  ziU8 graphTable;

  graphTable = 0x1a;
  keyTable = 0x1b;
  if (prefixLength != 0) {
    *prefixLength = 0;
  }
  if (reverseOrder != 0) {
    graphTable = 0x18;
    keyTable = 0x19;
  }
  if (Zi8GetTableSize(language & 0xff,graphTable,ZI_WORK) == 0) {
    if (graphTable == 0x1a) {
      graphTable = 0x18;
      keyTable = 0x19;
    }
    else {
      graphTable = 0x1a;
      keyTable = 0x1b;
    }
  }
  Zi8MatchROMdata0(elements,count,language & 0xff,output,capacity,1,status,graphTable,keyTable,0,(ziU8 *)prefixLength,
                   &ZI_WORK->dawgCtx,ZI_WORK->unk_0x1760,ZI_WORK);
  return;
}
