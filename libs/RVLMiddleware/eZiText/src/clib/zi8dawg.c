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

ziU32 Zi8MatchROMdata0(ziWChar* elements, ziU32 count, ziU8 language,
                      ziWChar* output, ziU16 capacity, ziU8 mode, ziU8 status,
                      ziU8 graphTable, ziU8 keyTable, ziU8 acceptPrefix,
                      ziU8* prefixLength, zi8DawgCtx* context, ziU8* search,
                      ziPtr __zi8_work_data) {
    ziBool searching;
    ziS32 tableSize;
    ziU8* graph;
    ziS16 key;
    ziU8 endOfWord;
    zi8DawgRec* current;
    ziU16 index;
    ziU16 depth;
    zi8DawgRec* records = context->recs;
    ziU8 result = 0;
    ziU32 keyCount;
    ziU8* table;
    ziS16 keys[3];

    if (language != context->lang || graphTable != context->key) {
        records[0].key = 0;
    }
    if ((ziU8)count != 1 || mode == 0 || graphTable != 0xe) {
        if (status != 0) {
            if (records[context->cnt - 1].node == (ziU8*)context->unk_0x338) goto finish_graph;
            for (index = 0; (ziU16)index < (ziU8)count; index++) {
                if (records[(ziU16)index].key != elements[(ziU16)index] &&
                    (records[(ziU16)index].attr & 0xffff) != elements[(ziU16)index]) goto finish_graph;
            }
            if (mode == 1) acceptPrefix = 0;
        } else {
            if (ZI_WORK->unk_0x141E == 0 || graphTable != 0xc ||
                (tableSize = Zi8GetTableSize(language, ZI_WORK->unk_0x141E, ZI_WORK)) == 0) {
                tableSize = Zi8GetTableSize(language, graphTable, ZI_WORK);
                if (tableSize == 0) {
                    Zi8LogError(0x961, ZI_WORK);
                    goto finish_graph;
                }
                table = (ziU8*)Zi8GetTableAddress(language, graphTable, ZI_WORK);
            } else {
                table = (ziU8*)Zi8GetTableAddress(language, ZI_WORK->unk_0x141E, ZI_WORK);
                keyTable = ZI_WORK->unk_0x141E + 1;
            }
            context->table = table;
            context->cap = (((ziU16)context->table[2] << 8) + (ziU16)context->table[3]) / 3;
            context->p08 = context->table + 4;
            context->p0C = context->table + context->cap * 2 + 4;
            context->lang = language;
            context->key = graphTable;
            index = 0;
            while ((ziU16)index < (ziU8)count && records[(ziU16)index].key == elements[(ziU16)index]) {
                index++;
            }
            if ((ziU16)index < 2) {
                key = Zi8GetTableSize(language, keyTable, ZI_WORK);
                if (key == 0 || ZI_WORK->userKeys[language] != 0) {
                    graph = ZiDAWGGetGraph(context);
                    records[0].node = graph;
                    context->unk_0x338 = 0;
                    context->p14 = 0;
                } else {
                    index = 0;
                    while (1) {
                        if ((ziU8)count < 2) keyCount = (ziU8)count;
                        else keyCount = 2;
                        if (keyCount <= (ziU16)index) break;
                        key = Zi8ConvertWC2Key(elements[(ziU16)index], language, ZI_WORK);
                        keys[(ziU16)index] = key;
                        if (keys[(ziU16)index] == 0) keys[(ziU16)index] = elements[(ziU16)index];
                        index++;
                    }
                    keys[(ziU16)index] = 0;
                    table = (ziU8*)Zi8GetTableAddress(language, keyTable, ZI_WORK);
                    context->p14 = table + 2;
                    records[0].node = ZiDAWGGetGraphInfo(context, table + context->cap * 2 + 2, keys);
                }
                records[0].key = 0;
                if (records[0].node == 0) goto finish_graph;
            } else {
                records[0].node = records[(ziU16)index - 1].back;
            }
            context->cnt = 1;
            search[1] = count;
            search[0] = 0;
            if (mode == 1) {
                search[0] = 1;
                acceptPrefix = 0;
            } else if (mode == 0 && acceptPrefix == 0) {
                search[1]++;
            }
        }
        searching = 1;
        depth = context->cnt;
        while ((current = &records[depth - 1], searching) && context->cnt != 0 &&
               current->node != (ziU8*)context->unk_0x338 && context->cnt <= capacity) {
            current->attr = ZiDAWGgetCHARattribute(context, current->node, ZI_WORK);
            if ((ziU8)count < context->cnt) {
check_word:
                if (context->cnt < search[1]) goto descend;
                if (search[0] == 0 || context->cnt <= search[1]) {
                    if (acceptPrefix != 0 || (endOfWord = ZiDAWGgetEOWattribute(current->node)) != 0) {
                        for (depth = 0; depth < context->cnt; depth++) {
                            output[depth] = records[depth].attr;
                        }
                        result = context->cnt;
                        searching = 0;
                        if (acceptPrefix != 0) goto next_sibling;
                    }
                    if (search[0] == 0 || context->cnt < search[1]) goto descend;
                }
next_sibling:
                while (context->cnt != 0) {
                    graph = ZiDAWGGetSibling(records[context->cnt - 1].node);
                    records[context->cnt - 1].node = graph;
                    if (records[context->cnt - 1].node != 0) break;
                    context->cnt--;
                }
            } else {
                if (context->p14 == 0) {
                    key = Zi8ConvertWC2Key(current->attr & 0xffff, language, ZI_WORK);
                } else {
                    key = (ziU16)context->p14[(current->attr >> 24) * 2] * 0x100 +
                          (ziU16)context->p14[(current->attr >> 24) * 2 + 1];
                }
                if (key != elements[context->cnt - 1] &&
                    (current->attr & 0xffff) != elements[context->cnt - 1]) goto next_sibling;
                if (current->key != elements[context->cnt - 1]) {
                    current->key = elements[context->cnt - 1];
                    current->back = records[0].node;
                    depth = context->cnt;
                    records[depth].key = 0;
                }
                if (prefixLength != 0 && *prefixLength < context->cnt &&
                    (endOfWord = ZiDAWGgetEOWattribute(current->node)) != 0) {
                    *prefixLength = context->cnt;
                    for (depth = 0; depth < context->cnt; depth++) output[depth] = records[depth].attr;
                }
                if ((ziU8)count <= context->cnt) goto check_word;
descend:
                graph = ZiDAWGGetChild(records[context->cnt - 1].node);
                records[context->cnt].node = graph;
                if (records[context->cnt].node == 0) goto next_sibling;
                context->cnt++;
                if (ZI_WORK->unk_0x141F < context->cnt) ZI_WORK->unk_0x141F = context->cnt;
            }
            depth = context->cnt;
        }
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

unsigned int Zi8MatchROMdata1(ziWChar *elements, ziU8 count, ziU8 language, ziWChar *output, ziU16 capacity, ziU8 mode, unsigned int status, ziU32 groupIndex, char *group, ziU8 acceptPrefix, ziPtr __zi8_work_data)
{
  unsigned int result;
  ziU32 tableAddress;

  result = 0;
  if ((status & 0xff) == 0) {
    ZI_WORK->unk_0x1764 = (ziU8*)group;
    if (ZI_WORK->unk_0x1764 == 0) {
      if (Zi8GetTableSize(language & 0xff,0xb,ZI_WORK) != 0) {
        tableAddress = Zi8GetTableAddress(language & 0xff,0xb,ZI_WORK);
        ZI_WORK->unk_0x1764 = (ziU8*)tableAddress;
      }
    }
    if (ZI_WORK->unk_0x1764 != 0) {
      for (; (*ZI_WORK->unk_0x1764 != 0xff && ((groupIndex & 0xff) != 0));
          groupIndex = groupIndex - 1) {
        while (*ZI_WORK->unk_0x1764 != 0xff) {
          ZI_WORK->unk_0x1764 += 2;
        }
        ZI_WORK->unk_0x1764++;
      }
    }
  }
  if (ZI_WORK->unk_0x1764 == 0) {
    result = Zi8MatchROMdata0(elements,count,language & 0xff,output,capacity & 0xffff,
                             mode & 0xff,status & 0xff,0,1,acceptPrefix,0,&ZI_WORK->dawgCtx,
                             ZI_WORK->unk_0x1760,ZI_WORK);
  }
  else {
    while (*ZI_WORK->unk_0x1764 != 0xff) {
      result = Zi8MatchROMdata0(elements,count,language & 0xff,output,
                               capacity & 0xffff,mode & 0xff,status & 0xff,
                               *ZI_WORK->unk_0x1764,
                               ZI_WORK->unk_0x1764[1],acceptPrefix,0,
                               &ZI_WORK->dawgCtx,ZI_WORK->unk_0x1760,ZI_WORK);
      if ((result & 0xff) != 0) break;
      ZI_WORK->unk_0x1764 += 2;
      status = 0;
    }
  }
  return result;
}

unsigned int Zi8MatchROMdata2(ziWChar *elements, unsigned int count, unsigned int language, ziWChar *output, unsigned int capacity, unsigned int mode, unsigned int status, ziU8 reservedMode, ziU8 *group, ziU8 acceptPrefix, ziPtr __zi8_work_data)
{
  ziU16 character;
  unsigned int result;
  ziU8 prefixCount;
  unsigned int index;
  unsigned int remaining;

  result = 0;
  if (reservedMode != 0) return 0;
    if ((status & 0xff) == 0) {
      ZI_WORK->unk_0x1768 = 0;
      ZI_WORK->unk_0x17EA = 0;
      if ((((group == 0) || (*group != '\f')) || ((language & 0xff) != 10)) ||
         (ZI_WORK->unk_0x141C == '\0')) {
        ZI_WORK->unk_0x141E = 0;
      }
      else {
        ZI_WORK->unk_0x141E = 0x10;
      }
    }
search_segment:
    ZI_WORK->unk_0x141F = 1;
    result = Zi8MatchROMdata1(elements + (unsigned int)ZI_WORK->unk_0x17EA,
                             count - ZI_WORK->unk_0x17EA & 0xff,language & 0xff,
                             &ZI_WORK->unk_0x17F4[ZI_WORK->unk_0x17EA],
                             capacity & 0xffff,mode & 0xff,status & 0xff,
                             ZI_WORK->unk_0x1768,(char *)group,acceptPrefix,ZI_WORK);
    if ((result & 0xff) == 0) {
      if ((((status & 0xff) != 0) || ((count & 0xff) == 1)) ||
         (((mode & 0xff) == 1 &&
          ((ZI_WORK->unk_0x1768 == 0 &&
           (prefixCount = Zi8MatchROMdata1(elements + (unsigned int)ZI_WORK->unk_0x17EA,
                                     count - ZI_WORK->unk_0x17EA & 0xff,language & 0xff,
                                     &ZI_WORK->unk_0x17F4[ZI_WORK->unk_0x17EA],
                                     capacity & 0xffff,0,status & 0xff,
                                     ZI_WORK->unk_0x1768,(char *)group,acceptPrefix,ZI_WORK),
           prefixCount != '\0')))))) goto finish_segments;
      index = Zi8GetTableCount(language & 0xff,0x1f,ZI_WORK);
      if ((index & 4) == 0) {
        for (index = 0; (index & 0xff) < (count & 0xff); index = index + 1) {
          if (elements[index & 0xff] == 0xeff1) goto finish_segments;
        }
      }
      if ((capacity & 0xffff) < (unsigned int)ZI_WORK->unk_0x141F) goto finish_segments;
      prefixCount = ZI_WORK->unk_0x141F;
      for (; prefixCount != 0; prefixCount--) {
        result = Zi8MatchROMdata1(elements + (unsigned int)ZI_WORK->unk_0x17EA,prefixCount,
                                 language & 0xff,
                                 &ZI_WORK->unk_0x17F4[ZI_WORK->unk_0x17EA],
                                 capacity & 0xffff,1,0,ZI_WORK->unk_0x1768,(char *)group,
                                 acceptPrefix,ZI_WORK);
        if ((result & 0xff) != 0) break;
      }
      if (prefixCount == 0) goto finish_segments;
      ZI_WORK->unk_0x17EA = ZI_WORK->unk_0x17EA + ((ziU16)result & 0xff);
      if ((unsigned int)ZI_WORK->unk_0x17EA == (count & 0xff)) {
        result = 0;
        goto finish_segments;
      }
      ZI_WORK->unk_0x1768 = ZI_WORK->unk_0x1768 + 1;
      status = 0;
      ZI_WORK->unk_0x141E = 0;
      if ((ZI_WORK->dawgCtx.key == 0) && ((language & 0xff) == 10)) {
        for (result = 0; (result & 0xff) < (unsigned int)ZI_WORK->unk_0x17EA; result = result + 1) {
          character = ZI_WORK->unk_0x17F4[result & 0xff];
          if (character == 0x6f) {
select_vowel_table:
            ZI_WORK->unk_0x141E = 0x10;
            break;
          }
          if (character < 0x6f) {
            if (character == 0x61) goto select_vowel_table;
          }
          else if (character == 0x75) goto select_vowel_table;
        }
      }
      goto search_segment;
    }
    for (remaining = ZI_WORK->unk_0x17EA + result & 0xff; (remaining & 0xff) != 0;
        remaining = remaining - 1) {
      output[(remaining & 0xff) - 1] = ZI_WORK->unk_0x17F4[(remaining & 0xff) - 1];
    }
    result = result + ZI_WORK->unk_0x17EA & 0xff;
finish_segments:
  return result;
}

ziU8 Zi8MatchROMdata(ziWChar *elements, ziU8 count, ziU8 language, ziWChar *output, ziU16 capacity, ziU8 mode, ziU8 status, ziU8 reservedMode, ziU8 acceptPrefix, ziPtr __zi8_work_data)
{
  ziU16 *input;
  ziU8* group;
  int tableSize;
  ziU8 found;
  unsigned int elementCount;
  unsigned int result;

  input = (ziU16 *)elements;
  elementCount = (unsigned int)count;
  result = 0;
  if ((capacity & 0xffff) < (elementCount & 0xff)) {
    Zi8LogError(0x321,ZI_WORK);
  }
  else if ((status & 0xff) == 2) {
    Zi8LogError(100,ZI_WORK);
  }
  else {
    if ((status & 0xff) == 0) {
      ZI_WORK->unk_0x17EC = 0;
      group = NextDawgGroup(0,language & 0xff,ZI_WORK);
      ZI_WORK->unk_0x17F0 = group;
    }
    else if (ZI_WORK->unk_0x17EC != '\0') {
      Zi8LogError(100,ZI_WORK);
      goto finish_match;
    }
    tableSize = Zi8GetTableSize(language & 0xff,0x1c,ZI_WORK);
    if (tableSize == 0) {
      result = Zi8MatchROMdata2(input,elementCount & 0xff,language & 0xff,output,capacity & 0xffff,
                               mode & 0xff,status & 0xff,reservedMode & 0xff,0,acceptPrefix,ZI_WORK);
    }
    else {
      while (((ZI_WORK->unk_0x17F0 != 0 &&
              (result = Zi8MatchROMdata2(input,elementCount & 0xff,language & 0xff,output,capacity & 0xffff,
                                        mode & 0xff,status & 0xff,reservedMode & 0xff,
                                        (ziU8 *)ZI_WORK->unk_0x17F0,acceptPrefix,ZI_WORK),
              (result & 0xff) == 0)) &&
             ((status = 0, 1 < (elementCount & 0xff) || ((language & 0xff) != 0x36))))) {
        group = NextDawgGroup(ZI_WORK->unk_0x17F0,language & 0xff,ZI_WORK);
        ZI_WORK->unk_0x17F0 = group;
      }
    }
    if (((((result & 0xff) == 0) && ((status & 0xff) == 0)) && ((mode & 0xff) == 1)) &&
       (((elementCount & 0xff) == 1 && ((capacity & 0xffff) != 0)))) {
      ZI_WORK->unk_0x17EC = 1;
      if (tableSize == 0) {
        found = Zi8MatchROMdata2(input,elementCount & 0xff,language & 0xff,output,capacity & 0xffff,0,
                                 status & 0xff,reservedMode & 0xff,0,acceptPrefix,ZI_WORK);
        if (found != '\0') {
          *output = *input;
          result = 1;
        }
      }
      else {
        group = NextDawgGroup(0,language & 0xff,ZI_WORK);
        ZI_WORK->unk_0x17F0 = group;
        while (ZI_WORK->unk_0x17F0 != 0) {
          found = Zi8MatchROMdata2(input,elementCount & 0xff,language & 0xff,output,capacity & 0xffff,0,
                                   status & 0xff,reservedMode & 0xff,(ziU8 *)ZI_WORK->unk_0x17F0,
                                   acceptPrefix,ZI_WORK);
          if (found != '\0') {
            *output = *input;
            result = 1;
            break;
          }
          group = NextDawgGroup(ZI_WORK->unk_0x17F0,language & 0xff,ZI_WORK);
          ZI_WORK->unk_0x17F0 = group;
        }
      }
    }
    Zi8LogError(100,ZI_WORK);
  }
finish_match:
  return (ziU8)result;
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
