"""Fresh bounded whole-Discovery actual PPC executions versus sequential reference.
Callees/callbacks obey explicit valid-buffer contracts; no hardware/formal claim.
"""
import sys
sys.dont_write_bytecode=True
from pathlib import Path
import json,hashlib,re,random,struct,itertools,time,os
from elftools.elf.elffile import ELFFile
from capstone import Cs,CS_ARCH_PPC,CS_MODE_32,CS_MODE_BIG_ENDIAN
import argparse
parser=argparse.ArgumentParser(description=__doc__)
for name in ['baseline','candidate','original','dol','symbols','output-dir']:parser.add_argument('--'+name,required=True,type=Path)
args=parser.parse_args();NAME='ATERMDiscoverAccessPoints'

OUT=args.output_dir.resolve();OUT.mkdir(parents=True,exist_ok=False)
def write(n,x):(OUT/n).write_text(json.dumps(x,indent=2)+'\n')

def plain(x):
 if hasattr(x,'items'):return {k:plain(v) for k,v in x.items()}
 if isinstance(x,(list,tuple)):return [plain(v) for v in x]
 return x

def metadata(path):
 with path.open('rb') as f:
  obj=ELFFile(f);sections=[dict(name=z.name,header=plain(z.header),data=z.data()) for z in obj.iter_sections()];symbols=[dict(name=z.name,entry=plain(z.entry)) for z in obj.get_section_by_name('.symtab').iter_symbols()];functions={};relocations={}
  for z in obj.get_section_by_name('.symtab').iter_symbols():
   if z['st_info']['type']=='STT_FUNC' and isinstance(z['st_shndx'],int) and z['st_size']:
    sec=obj.get_section(z['st_shndx']);a=z['st_value'];n=z['st_size'];functions[z.name]=dict(section=sec.name,address=a,size=n,body=sec.data()[a:a+n])
  for z in obj.iter_sections():
   if z['sh_type']=='SHT_RELA':relocations[z.name]=[plain(r.entry) for r in z.iter_relocations()]
  return dict(header=plain(obj.header),sections=sections,symbols=symbols,functions=functions,relocations=relocations)
mb=metadata(args.baseline);mc=metadata(args.candidate);assert mb['header']==mc['header'];assert len(mb['sections'])==len(mc['sections']);assert len(mb['symbols'])==len(mc['symbols'])==145;sectionchanges=[];pairs=[]
for b,c in zip(mb['sections'],mc['sections']):
 assert b['name']==c['name'] and b['header']==c['header']
 if b['data']!=c['data']:assert b['name'] in ['.text','.rela.text','.strtab'];sectionchanges.append(b['name'])
for i,(b,c) in enumerate(zip(mb['symbols'],mc['symbols'])):
 assert b['entry']==c['entry']
 if b['name']!=c['name']:
  ent=b['entry'];sec=mb['sections'][ent['st_shndx']];assert ent['st_info']==dict(bind='STB_LOCAL',type='STT_OBJECT');assert sec['data']==mc['sections'][ent['st_shndx']]['data'];extent=sec['data'][ent['st_value']:ent['st_value']+ent['st_size']];pairs.append(dict(index=i,old=b['name'],new=c['name'],entry=ent,section=sec['name'],extent_sha256=hashlib.sha256(extent).hexdigest()))
assert [(x['index'],x['old'],x['new']) for x in pairs]==[(22,'@2652','@2680'),(23,'@2704','@2732'),(24,'@1036','@1018'),(25,'@2844','@2872')]
assert mb['functions'].keys()==mc['functions'].keys();siblings=[]
for name,fn in mb['functions'].items():
 if name!=NAME:assert fn==mc['functions'][name];siblings.append(name)
assert len(siblings)==25;assert mb['functions']['ATERMBuildAssociationRequest']==mc['functions']['ATERMBuildAssociationRequest']
begin=mb['functions'][NAME]['address'];end=begin+mb['functions'][NAME]['size'];bt=next(z['data'] for z in mb['sections'] if z['name']=='.text');ct=next(z['data'] for z in mc['sections'] if z['name']=='.text');assert bt[:begin]==ct[:begin] and bt[end:]==ct[end:];assert mb['functions'][NAME]['size']==mc['functions'][NAME]['size']==1044
relmaps=[];assert mb['relocations'].keys()==mc['relocations'].keys()
for sec,rows in mb['relocations'].items():
 assert len(rows)==len(mc['relocations'][sec])
 for i,(b,c) in enumerate(zip(rows,mc['relocations'][sec])):
  assert b['r_info']==c['r_info'] and b['r_addend']==c['r_addend'];offset=b['r_offset']-begin;expected=b['r_offset']+(4 if sec=='.rela.text' and offset==0x224 else 8 if sec=='.rela.text' and 0x2bc<=offset<0x3a4 else 0);assert c['r_offset']==expected
  if b!=c:relmaps.append(dict(section=sec,index=i,baseline=b,candidate=c))
assert len(relmaps)==14
write('exact-metadata-audit.json',dict(pass_all=True,all_section_headers_symbol_entries_and_allocated_nontext_identical=True,all25_sibling_bodies_addresses_extents_and_Association_identical=True,exact_four_local_name_pairs=pairs,precise14_owned_relocation_offset_changes=relmaps,all_other_relocation_fields_and_entries_identical=True,section_data_changes=sectionchanges,no_broad_name_normalization=True))
MASK=0xffffffff;u32=lambda v:v&MASK;s32=lambda v:v-0x100000000 if v&0x80000000 else v
SD=0x20000000;SB=0x20010000;BS=0x21000000;SP=0x60000200;FRAME=SP-0x90;RET=0x81234560;CLOCK=0x800000f8
HC=0x10000000;HP=0x10010000;HR=0x10020000;ALLOC=0xa1000000;PROGRESS=0xa1000100;FREE=0xa1000200;FREE2=0xa1000300
BASES={'.sdata':SD,'.sbss':SB,'.bss':BS};DEC=Cs(CS_ARCH_PPC,CS_MODE_32|CS_MODE_BIG_ENDIAN)
def load(p):
 with p.open('rb') as f:
  obj=ELFFile(f);st=obj.get_section_by_name('.symtab');fn=st.get_symbol_by_name(NAME)[0];a=fn['st_value'];n=fn['st_size'];raw=obj.get_section(fn['st_shndx']).data()[a:a+n];rels={}
  for z in obj.iter_sections():
   if z['sh_type']!='SHT_RELA' or z['sh_info']!=fn['st_shndx']:continue
   sy=obj.get_section(z['sh_link'])
   for rr in z.iter_relocations():
    if a<=rr['r_offset']<a+n:
     sm=sy.get_symbol(rr['r_info_sym']);sid=sm['st_shndx'];pc=(rr['r_offset']-a)&~3;assert pc not in rels
     rels[pc]=dict(type=rr['r_info_type'],name=sm.name,addend=rr['r_addend'],section=obj.get_section(sid).name if isinstance(sid,int) else sid,value=sm['st_value'])
  ins={i.address:(i.mnemonic,i.op_str) for i in DEC.disasm(raw,0)};assert len(ins)*4==n;return dict(raw=raw,ins=ins,rels=rels)
B=load(args.baseline);C=load(args.candidate);T=load(args.original);assert len(B['ins'])==len(C['ins'])==261 and len(T['ins'])==263
# B/C unchanged actual regions are byte-identical, including all callback/scan prefix and cleanup.
prefix_branch_maps=[]
for pc in range(0,0x220,4):
 mn,op=B['ins'][pc];expected=op
 if mn in ['b','bne','beq','bge','blt','ble','bgt']:
  dest=int(op,0);expected=hex(dest+8) if dest in [0x2bc,0x338,0x34c] else op
 assert C['ins'][pc]==(mn,expected)
 if expected!=op:prefix_branch_maps.append(dict(offset=pc,baseline_target=op,candidate_target=expected))
assert len(prefix_branch_maps)==5;assert B['raw'][0x3ac:]==C['raw'][0x3ac:]
# After the formatter, unchanged progress/loop code moves by8 exactly.
for pc in range(0x2bc,0x34c,4):
 mn,op=B['ins'][pc];cm,co=C['ins'][pc+8];expected=op
 if mn in ['b','bne','beq','bge','blt','ble','bgt']:expected=hex(int(op,0)+8) if int(op,0)>=0x2bc else op
 if mn=='bl':assert B['rels'][pc]==C['rels'][pc+8];expected=hex(pc+8)
 assert (cm,co)==(mn,expected),(hex(pc),(mn,op),(cm,co),expected)
assert C['ins'][0x220]==('li','r0, 6') and C['ins'][0x238]==('mtctr','r0') and C['ins'][0x2b4]==('bdnz','0x23c')
assert C['ins'][0x358]==('bge','0x390') and C['ins'][0x390]==('li','r26, -3')
# Validate original DOL and actual helper implementations.
dol=(args.dol).read_bytes();assert hashlib.sha1(dol).hexdigest()=='26116613f624061ba99c8d1a299aaa6efa85670d'
words=lambda off:struct.unpack_from('>18I',dol,off);sections=list(zip(words(0),words(0x48),words(0x90)))
def at(a,n):
 for fo,va,z in sections:
  if va<=a and a+n<=va+z:return dol[fo+a-va:fo+a-va+n]
 raise AssertionError(('DOL',hex(a),n))
syms={n:int(a,16) for n,a in re.findall(r'^([^\s=]+) = \.[^\s:]+:0x([0-9A-Fa-f]+);',(args.symbols).read_text(),re.M)};nonrel=0;direct=[]
for pc in T['ins']:
 if pc not in T['rels']:assert T['raw'][pc:pc+4]==at(syms[NAME]+pc,4);nonrel+=1
for pc,z in T['rels'].items():
 if z['type']==10:
  w=int.from_bytes(at(syms[NAME]+pc,4),'big');d=w&0x3fffffc;d-=0x4000000 if d&0x2000000 else 0;assert syms[NAME]+pc+d==syms[z['name']]+z['addend'];direct.append(dict(offset=pc,name=z['name'],destination=syms[z['name']]+z['addend']))
helpers={}
for name,mn in [('_savegpr_14','stw'),('_restgpr_14','lwz')]:
 ins=[(i.mnemonic,i.op_str) for i in DEC.disasm(at(syms[name],76),0)];assert len(ins)==19
 for i,r in enumerate(range(14,32)):
  q=re.fullmatch(r'r(\d+), (-?(?:0x[0-9a-f]+|\d+))\(r11\)',ins[i][1]);assert q and ins[i][0]==mn and int(q[1])==r and int(q[2],0)==-4*(32-r)
 assert ins[-1][0]=='blr';helpers[name]=ins
class Memory:
 def __init__(self):self.regions=[];self.trace=[];self.leases=[]
 def add(self,a,n,seed):self.regions.append((a,bytearray((seed+i*31)&255 for i in range(n))))
 def locate(self,a,n,check=True):
  for base,b in self.regions:
   if base<=a and a+n<=base+len(b):
    if check and base in [HC,HP,HR]:assert any(x<=a and a+n<=x+z for x,z in self.leases),('outside active allocation',hex(a),n,self.leases)
    return b,a-base
  raise AssertionError(('outside region',hex(a),n))
 def visible(self,a):return not SP-0x200<=a<SP+0x100 or FRAME+0x18<=a<FRAME+0x38
 def read(self,a,n,trace=True):
  b,i=self.locate(a,n,trace);v=bytes(b[i:i+n])
  if trace and self.visible(a):self.trace.append(('read',a,n,v.hex()))
  return v
 def write(self,a,v,trace=True):
  b,i=self.locate(a,len(v),trace);b[i:i+len(v)]=v
  if trace and self.visible(a):self.trace.append(('write',a,len(v),v.hex()))
 def get(self,a,n=4,trace=True):return int.from_bytes(self.read(a,n,trace),'big')
 def put(self,a,v,n=4,trace=True):self.write(a,(v&((1<<(8*n))-1)).to_bytes(n,'big'),trace)
 def state(self):return [(a,bytes(b)) for a,b in self.regions]
def fixture(c):
 m=Memory();seed=c['seed']
 for a,n,k in [(SD,56,1),(SB,80,2),(BS,8160,3),(SP-0x200,0x300,4),(CLOCK,4,5),(HC,0x2000,6),(HP,0x2000,7),(HR,0x2000,8)]:m.add(a,n,seed+k*17)
 for a,v in [(SD,c['deadline']),(SD+4,c['limit']),(SB,0),(SB+4,0),(SB+8,PROGRESS),(SB+12,ALLOC),(SB+16,FREE),(SB+76,c['initial_cancel']),(CLOCK,c['bus_clock'])]:m.put(a,v,trace=False)
 m.write(SD+32,b'******\0',False);m.write(SB+68,bytes.fromhex(c['mac']),False)
 caller=[u32(0x91000000+i*0x12345+seed) for i in range(32)];caller[1]=SP;return m,caller

def quotient(a,b):assert b;return (-1 if (a<0)!=(b<0) else 1)*(abs(a)//abs(b))
class Hooks:
 def __init__(self,m,c):self.m=m;self.c=c;self.trace=[];self.count=0;self.allocs=0;self.scans=0;self.progresses=0;self.clocks=0;self.frees=0;self.formatted=False;self.selected_index=None
 def call(self,name,args):
  m=self.m;c=self.c;self.count+=1;self.trace.append((name,tuple(args)));m.trace.append(('call',name,tuple(args)))
  if name in ['allocate']:
   self.allocs+=1;n=args[0]
   if c['fail_alloc']==self.allocs:return 0
   off=[0,4,16,28][c['layout']];ptr=[HC+off,HP+off,HR+[0,1,3,31][c['layout']]][self.allocs-1];assert n<0x1000;m.locate(ptr,n,False);m.leases.append((ptr,n));return ptr
  if name in ['release','release_alt']:
   self.frees+=1;ptr=args[0];entry=next(x for x in m.leases if x[0]==ptr);m.put(ptr,c['seed']^self.frees);m.leases.remove(entry)
   if c['callback']==3 and self.frees==1:m.put(SB+16,FREE2);m.put(SB+4,0xdeadbeef)
   return 0x9a000000+self.frees
  if name=='memset':a,v,n=args;m.write(a,bytes([v&255])*n);return a
  if name=='memcpy':
   dst,src,n=args;assert dst+n<=src or src+n<=dst,('memcpy overlap',args);v=m.read(src,n);m.write(dst,v);return dst
  if name=='strcpy':
   dst,src=args;v=bytearray()
   for i in range(33):
    x=m.get(src+i,1);v.append(x)
    if x==0:break
   else:raise AssertionError('unterminated valid ssid')
   assert dst+len(v)<=src or src+len(v)<=dst;m.write(dst,v);return dst
  if name=='OSGetTime':
   self.clocks+=1;ms=c['final_ms'] if self.clocks==c['final_clock_call'] else c['head_ms'];bus=m.get(CLOCK,trace=False);ticks=ms*(bus//4//1000)
   if c['callback']==4 and self.clocks==1:m.put(SD,c['mutated_deadline']);m.put(SB+76,c['callback_cancel']);m.put(CLOCK,24000000)
   return ticks&0xffffffffffffffff
  if name=='__div2i':
   ah,al,bh,bl=args;a=(ah<<32)|al;b=(bh<<32)|bl;a-=1<<64 if a&(1<<63) else 0;b-=1<<64 if b&(1<<63) else 0;assert b>0;return quotient(a,b)&0xffffffffffffffff
  if name=='ATERMScanAccessPoints':
   self.scans+=1;dst,size=args;m.locate(dst,size)
   if c['mode']=='scan_error':return u32(c['scan_error'])
   if c['mode']=='oversize':return c['limit']
   count=c['count'];selected=c['mode'] in ['select','late_select'] and self.scans>=c['select_scan']
   for i in range(count):
    at=dst+2+i*48;m.put(at,24,2);m.write(at+4,bytes.fromhex(c['mac']) if i==c['select_index'] else bytes([i+17]*6));length=c['ssid_length'];text=b'******' if selected and i==c['select_index'] else b'OTHER!';m.put(at+10,length,2);m.write(at+12,(text+b'\0'*32)[:32]);m.put(at+44,c['capabilities'],2)
   if c['callback']==1:m.put(SB+76,1)
   if c['callback']==2:m.put(SB,1);m.put(SB+4,0xffffff9d)
   return count
  if name=='ATERMFindChangedApRecord':
   cur,prev,out=args;cc=m.get(cur,trace=False);pp=m.get(prev,trace=False);assert cc<=c['limit'] and pp<=c['limit'];chosen=None
   def record(base,i):
    p=base+4+i*48;length=m.get(p,trace=False);assert length<=32;text=m.read(p+4,32,False).split(b'\0',1)[0];mac=m.read(p+40,6,False);status=m.get(p+46,2,False);return length,text,mac,status
   for i in range(cc):
    length,text,mac,status=record(cur,i)
    if length and not (length==1 and text in [b'',b' ']):
     for j in range(pp):
      _,pt,pm,ps=record(prev,j)
      if pt.startswith(text) and mac==pm and status!=ps and status==0:chosen=i;break
    if chosen is not None:break
   if chosen is None:
    had=any(record(prev,j)[1].startswith(b'******') and record(prev,j)[3]==0 for j in range(pp))
    for i in range(cc):
     _,text,_,status=record(cur,i)
     if text==b'******' and status==0 and not had:chosen=i;break
   if chosen is not None:m.put(out,chosen);self.selected_index=chosen;return 1
   return 0
  if name=='progress':
   assert args==[FRAME+0xc];self.progresses+=1;snapshot=m.read(args[0],12,False);self.trace.append(('progress_snapshot',snapshot.hex()));m.trace.append(('progress_snapshot',snapshot.hex()))
   if c['mode']=='wait' and self.progresses==c['stop_after']:m.put(SB+76,1)
   if c['callback']==3:m.put(SB+4,0xffffffed);m.write(SB+68,b'MUTATE');m.put(SB+16,FREE2)
   return 0x81777777
  raise AssertionError(('callee',name,args))

def mask(mb,me):return sum(1<<(31-i) for i in (range(mb,me+1) if mb<=me else list(range(mb,32))+list(range(0,me+1))))
def execute(obj,c):
 m,caller=fixture(c);hooks=Hooks(m,c);r=caller.copy();pc=0;lr=RET;cr=0;ctr=c['seed'];coverage=set();steps=0
 def val(x):return r[int(x[1:])]
 def relocaddr(pc):z=obj['rels'][pc];assert z['section'] in BASES;return BASES[z['section']]+z['value']+z['addend']
 def ea(op,pc):
  if pc in obj['rels']:assert obj['rels'][pc]['type']==109;return relocaddr(pc)
  q=re.fullmatch(r'(-?(?:0x[0-9a-f]+|\d+))\((r\d+|0)\)',op);assert q,op;return u32((0 if q[2]=='0' else val(q[2]))+int(q[1],0))
 def call(name,args):
  nonlocal ctr,cr,lr
  result=hooks.call(name,args)
  for k in [0,*range(3,13)]:r[k]=u32(0xb0000000+hooks.count*0x100+k+c['seed'])
  cr=1;ctr=u32(0xc0000000+hooks.count+c['seed'])
  if name in ['OSGetTime','__div2i']:r[3]=(result>>32)&MASK;r[4]=result&MASK
  else:r[3]=u32(result)
 while True:
  steps+=1;assert steps<100000;coverage.add(pc);mn,op=obj['ins'][pc];p=op.split(', ');nxt=pc+4
  if mn in ['lwz','lhz','lbz']:r[int(p[0][1:])]=m.get(ea(p[1],pc),{'lwz':4,'lhz':2,'lbz':1}[mn])
  elif mn in ['stw','sth','stb']:m.put(ea(p[1],pc),val(p[0]),{'stw':4,'sth':2,'stb':1}[mn])
  elif mn=='stwu':addr=ea(p[1],pc);m.put(addr,val(p[0]));r[1]=addr
  elif mn=='mflr':r[int(p[0][1:])]=lr
  elif mn=='mtlr':lr=val(p[0])
  elif mn=='mtctr':ctr=val(p[0])
  elif mn=='mr':r[int(p[0][1:])]=val(p[1])
  elif mn=='li':r[int(p[0][1:])]=relocaddr(pc) if pc in obj['rels'] else u32(int(p[1],0))
  elif mn=='lis':r[int(p[0][1:])]=u32(((relocaddr(pc)+0x8000)>>16)<<16) if pc in obj['rels'] else u32(int(p[1],0)<<16)
  elif mn in ['addi','addic','addis']:
   imm=int(p[2],0)
   if pc in obj['rels']:assert obj['rels'][pc]['type']==4;imm=relocaddr(pc)&0xffff;imm-=0x10000 if imm&0x8000 else 0
   r[int(p[0][1:])]=u32((0 if p[1]=='0' else val(p[1]))+(imm<<(16 if mn=='addis' else 0)))
  elif mn=='mulli':r[int(p[0][1:])]=u32(s32(val(p[1]))*int(p[2],0))
  elif mn=='and':r[int(p[0][1:])]=val(p[1])&val(p[2])
  elif mn=='add':r[int(p[0][1:])]=u32(val(p[1])+val(p[2]))
  elif mn=='subf':r[int(p[0][1:])]=u32(val(p[2])-val(p[1]))
  elif mn=='mulhwu':r[int(p[0][1:])]=(val(p[1])*val(p[2])>>32)&MASK
  elif mn=='slwi':r[int(p[0][1:])]=u32(val(p[1])<<int(p[2],0))
  elif mn=='srwi':r[int(p[0][1:])]=val(p[1])>>int(p[2],0)
  elif mn=='rlwinm':sh,mb,me=map(lambda x:int(x,0),p[2:]);x=val(p[1]);r[int(p[0][1:])]=u32(((x<<sh)|(x>>(32-sh)))&mask(mb,me))
  elif mn=='clrlwi':r[int(p[0][1:])]=val(p[1])&((1<<(32-int(p[2],0)))-1)
  elif mn in ['cmpwi','cmplwi','cmpw','cmplw']:
   x=val(p[0]);y=val(p[1]) if mn in ['cmpw','cmplw'] else int(p[1],0)
   if mn in ['cmpwi','cmpw']:x=s32(x);y=s32(y&MASK)
   cr=(x>y)-(x<y)
  elif mn in ['b','beq','bne','bgt','bge','blt','ble']:
   if {'b':True,'beq':cr==0,'bne':cr!=0,'bgt':cr>0,'bge':cr>=0,'blt':cr<0,'ble':cr<=0}[mn]:nxt=int(p[-1],0)
  elif mn=='bdnz':ctr=u32(ctr-1);nxt=int(p[0],0) if ctr else nxt
  elif mn=='bl':
   z=obj['rels'][pc];assert z['type']==10 and z['addend']==0;name=z['name'];lr=nxt
   if name in helpers:
    # Execute the checked DOL helper instructions, not a synthetic ABI assumption.
    for hm,ho in helpers[name][:-1]:
     hp=ho.split(', ');addr=ea(hp[1],-1)
     if hm=='stw':m.put(addr,val(hp[0]))
     else:r[int(hp[0][1:])]=m.get(addr)
   else:arity={'memcpy':3,'memset':3,'strcpy':2,'ATERMScanAccessPoints':2,'ATERMFindChangedApRecord':3,'OSGetTime':0,'__div2i':4}[name];call(name,r[3:3+arity])
  elif mn=='bctrl':
   name={ALLOC:'allocate',PROGRESS:'progress',FREE:'release',FREE2:'release_alt'}[ctr];args=r[3:4];lr=nxt;call(name,args)
  elif mn=='blr':
   assert lr==RET and r[1]==SP and r[14:32]==caller[14:32];return dict(result=s32(r[3]),calls=hooks.trace,trace=m.trace,memory=m.state(),coverage=coverage,steps=steps,clocks=hooks.clocks,scans=hooks.scans,progresses=hooks.progresses,frees=hooks.frees,selected_index=hooks.selected_index)
  else:raise AssertionError(('unsupported opcode',hex(pc),mn,op))
  pc=nxt

def reference(c):
 m,caller=fixture(c);hooks=Hooks(m,c);m.put(FRAME,SP);m.put(FRAME+0x94,RET)
 for r in range(14,32):m.put(SP-4*(32-r),caller[r])
 def indirect(address,ptr):return hooks.call({ALLOC:'allocate',PROGRESS:'progress',FREE:'release',FREE2:'release_alt'}[address],[ptr])
 def clock():
  ticks=hooks.call('OSGetTime',[]);bus=m.get(CLOCK);divisor=bus//4//1000;assert divisor>0;q=hooks.call('__div2i',[ticks>>32,ticks&MASK,0,divisor]);return q&MASK
 result=-1;iteration=0;raw_scan=0;cur=0;prev=0;record_bytes=u32(m.get(SD+4)*48+52);m.put(FRAME+8,0);m.put(FRAME+0x38,0)
 fn=m.get(SB+12);cur=indirect(fn,record_bytes)
 if cur:hooks.call('memset',[cur,0,record_bytes])
 if cur:
  fn=m.get(SB+12);prev=indirect(fn,record_bytes)
  if prev:hooks.call('memset',[prev,0,record_bytes])
 if cur and prev:
  scan_bytes=u32(m.get(SD+4)*256);fn=m.get(SB+12);raw_scan=indirect(fn,scan_bytes+64);m.put(FRAME+0x38,raw_scan);scan=(raw_scan+31)&~31;first=scan+2;error=False
  while iteration<300 and m.get(SB+76)==0:
   now=clock()
   if now>=m.get(SD):break
   result=s32(hooks.call('ATERMScanAccessPoints',[scan,scan_bytes]))
   if result<0:error=True;break
   if m.get(SB+76):break
   if result>=s32(m.get(SD+4)):result=-6;error=True;break
   desc=first
   for index in range(result):
    entry=cur+index*48;hooks.call('memcpy',[entry+8,desc+12,32]);length=m.get(desc+10,2);m.put(entry+4,0 if length>32 else length);length=m.get(entry+4);m.put(entry+8+length,0,1);cap=m.get(desc+44,2);m.put(entry+50,(cap>>4)&1,2);hooks.call('memcpy',[entry+44,desc+4,6]);desc+=m.get(desc,2)*2
   m.put(cur,result)
   if m.get(SB)!=1 and hooks.call('ATERMFindChangedApRecord',[cur,prev,FRAME+8]):
    idx=m.get(FRAME+8);m.put(SB+28,idx);entry=cur+idx*48;hooks.call('strcpy',[BS+2340,entry+8]);hooks.call('memcpy',[SB+68,entry+44,6]);out=FRAME+0x18
    for i in range(6):
     byte=m.get(SB+68+i,1);hi=byte//16;lo=byte%16;m.put(out,hi+(48 if hi<=9 else 55),1);m.put(out+1,lo+(48 if lo<=9 else 55),1);m.put(out+2,0,1);out+=2
     if i<5:m.put(out,58,1);out+=1
    m.put(out,0,1);break
   hooks.call('memcpy',[prev,cur,record_bytes]);progress_deadline=m.get(SD);m.put(SB,2);m.put(FRAME+0xc,2)
   if progress_deadline==MASK:m.put(FRAME+0x10,MASK)
   else:now=clock();m.put(FRAME+0x10,u32(m.get(SD)-now))
   value=m.get(SB+4);fn=m.get(SB+8);m.put(FRAME+0x14,value);indirect(fn,FRAME+0xc);iteration+=1
  if not error:
   if iteration>=300:result=-3
   else:
    now=clock()
    if now>m.get(SD):result=-3
    else:result=1;result=-8 if m.get(SB+76) else result
 for ptr in [raw_scan,cur,prev]:
  if ptr:fn=m.get(SB+16);indirect(fn,ptr)
 return dict(result=result,calls=hooks.trace,trace=m.trace,memory=m.state(),clocks=hooks.clocks,scans=hooks.scans,progresses=hooks.progresses,frees=hooks.frees,selected_index=hooks.selected_index)

def case(**kw):
 c=dict(mode='select',count=1,select_index=0,select_scan=1,stop_after=1,deadline=100,head_ms=0,final_ms=0,limit=3,initial_cancel=0,fail_alloc=0,ssid_length=6,capabilities=0,scan_error=-7,callback=0,callback_cancel=1,mutated_deadline=0,bus_clock=243000000,layout=0,mac='000102030405',seed=0)
 c.update(kw)
 if c['mode'] in ['select','late_select']:c['final_clock_call']=c['select_scan']+(c['select_scan']-1)*(c['deadline']!=MASK)+1
 elif c['mode']=='wait':c['final_clock_call']=c['stop_after']*(1+(c['deadline']!=MASK))+1
 else:c['final_clock_call']=1 if c['initial_cancel'] else 2
 return c
cases=[]
for value,pos in itertools.product(range(256),range(6)):
 mac=bytearray([0xa5]*6);mac[pos]=value;cases.append(case(mac=mac.hex(),seed=len(cases),layout=pos%4))
for mode,stop,dl,offset in itertools.product(['wait','late_select'],[1,2,299,300],[1,2,0x7fffffff,MASK],[-1,0,1,2]):
 final=u32(dl+offset);cases.append(case(mode=mode,stop_after=stop,select_scan=stop,deadline=dl,final_ms=final,seed=len(cases),layout=stop%4,count=2,select_index=1))
for mode,cb,layout in itertools.product(['select','wait','scan_error','oversize'],range(5),range(4)):
 cases.append(case(mode=mode,callback=cb,layout=layout,stop_after=2,seed=len(cases),count=2,select_index=1))
for fail,layout in itertools.product([1,2],range(4)):cases.append(case(fail_alloc=fail,layout=layout,seed=len(cases)))
for cancel,dl,head,final,length,bus in itertools.product([0,1],[0,1,MASK],[0,1],[0,1],[0,1,32,33],[4000,24000000]):
 cases.append(case(initial_cancel=cancel,deadline=dl,head_ms=head,final_ms=final,ssid_length=length,bus_clock=bus,seed=len(cases),mode='wait',stop_after=1))
# Count-zero and protected-state loops, deterministic arbitrary clocks/MACs and callback cases.
rng=random.Random(202610040050)
for i in range(64):cases.append(case(mac=rng.randbytes(6).hex(),mode=rng.choice(['select','wait','scan_error','oversize']),count=i%3,ssid_length=rng.choice([0,1,6,32,33]),callback=i%5,layout=i%4,stop_after=1+(i%3),deadline=rng.choice([0,1,100,MASK]),head_ms=0,final_ms=rng.choice([0,1,100,MASK]),bus_clock=rng.choice([4000,243000000,MASK]),seed=len(cases)))
write('ppc-path-inputs.json',cases);cover={n:set() for n in ['baseline','candidate','target']};dig=hashlib.sha256();start=time.time();classes={};maximum=0
for number,c in enumerate(cases):
 rr=reference(c)
 for name,obj in [('baseline',B),('candidate',C),('target',T)]:
  got=execute(obj,c)
  for key in ['result','calls','trace','memory','clocks','scans','progresses','frees','selected_index']:
   if got[key]!=rr[key]:
    def discrepancy(a,b):
     if isinstance(a,list) and isinstance(b,list):
      for k,(x,y) in enumerate(zip(a,b)):
       if x!=y:return dict(index=k,actual=repr(x)[:600],reference=repr(y)[:600])
      return dict(actual_length=len(a),reference_length=len(b))
     return dict(actual=repr(a),reference=repr(b))
    write('model-failure.json',dict(case_number=number,object=name,key=key,case=c,discrepancy=discrepancy(got[key],rr[key])));raise AssertionError(('behavior/oracle mismatch',number,name,key))
  cover[name].update(got['coverage']);maximum=max(maximum,got['steps'])
 key=str((rr['result'],rr['clocks'],rr['scans'],rr['progresses'],rr['frees'],rr['selected_index'] is not None));classes[key]=classes.get(key,0)+1;dig.update(json.dumps(c,sort_keys=True).encode());dig.update(repr(rr['trace']).encode());dig.update(repr(rr['memory']).encode())
for name,obj in [('baseline',B),('candidate',C),('target',T)]:assert cover[name]==set(obj['ins']),('missing instruction coverage',name,sorted(set(obj['ins'])-cover[name]))
write('ppc-path-audit.json',dict(pass_all=True,cases=len(cases),actual_ppc_executions=len(cases)*3,independent_sequential_reference_executions=len(cases),coverage={n:dict(covered=len(v),total=len(obj['ins']),offsets=sorted(v)) for n,v,obj in [(n,cover[n],o) for n,o in [('baseline',B),('candidate',C),('target',T)]]},result_call_order_all_nonstack_memory_and_formatter_store_traces_and_complete_allocated_state_equal=True,actual_save_restore_helpers_verified_against_dol=True,all_nonvolatile_stack_lr_preserved=True,raw_target_words_verified=nonrel,actual_direct_calls_verified=direct,all256_byte_values_at_every_six_mac_positions=True,reachable_iteration299_and300_paths_exercised=True,iterations_beyond300_unreachable_under_checked_loop_and_ABI=True,callback_profiles=5,valid_allocation_layouts=4,case_classes=classes,result_digest=dig.hexdigest(),max_actual_steps=maximum,elapsed_seconds=time.time()-start,limits=['Bounded whole-function actual PPC interpreter and sequential source reference, not hardware or formal proof','External memcpy/memset/strcpy/scan/find/time/division/allocator/progress/release contracts are modeled; complete SDK or external callback internals are not executed','Exact original DOL save/restore helpers and all nonrelocated words/direct-call addresses are checked; concrete ELF relocations are rebased to private model allocations','All actual caller nonstack read/write traces, formatter private-stack writes and complete allocated final state are compared; other private frame accesses are ABI-checked rather than treated as external observable order','Fixed four valid disjoint allocation/alignment layouts and five legitimate callback profiles; no overlapping memcpy/strcpy or invalid effective-type alias is introduced','First/second allocation failures are modeled; the unchecked third allocation failure is excluded by requiring a valid raw scan buffer, without claiming all such failures necessarily produce undefined behavior','Scan counts0..2, initialized descriptors, bounded valid record indices/SSID strings, positive nonzero timer divisor; not arbitrary malformed descriptors or all64-bit time Cartesian inputs','Every raw MAC byte value per position and selected boundary/callback cases, not exhaustive2^48 MAC domain or every callback program','Existing private selectedMacText storage is modeled because original actually writes it; no new dummy output objects'],no_formal_or_hardware_claim=True));print('DISCOVERY PPC REFERENCE PASS',len(cases),'cases',len(cases)*3,'actualexecutions;fullcoverage', {n:len(v) for n,v in cover.items()},flush=True)
