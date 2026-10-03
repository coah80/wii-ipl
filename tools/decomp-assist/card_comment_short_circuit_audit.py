"""Fresh bounded actual-PPC comment/return paths versus sequential source reference.
No full CARD implementation, image-prefix execution, hardware or formal proof.
"""
import sys
sys.dont_write_bytecode=True
from pathlib import Path
import hashlib,json,random,re,struct,itertools,time,os
import argparse
P=argparse.ArgumentParser(description=__doc__)
for name in ["baseline","candidate","original","dol","symbols"]:P.add_argument("--"+name,type=Path,required=True)
P.add_argument("--output-dir",type=Path,required=True)
args=P.parse_args()
NAME="loadCardFileIcons"
from elftools.elf.elffile import ELFFile
from capstone import Cs,CS_ARCH_PPC,CS_MODE_32,CS_MODE_BIG_ENDIAN
OUT=args.output_dir.resolve();OUT.mkdir(parents=True,exist_ok=True)
assert not (OUT/'ppc-path-audit.json').exists() and not (OUT/'ppc-path-inputs.json').exists(), 'Use a fresh output directory'
def write(n,v):(OUT/n).write_text(json.dumps(v,indent=2)+'\n')
MASK=0xffffffff
s32=lambda x:x-0x100000000 if x&0x80000000 else x
sha=lambda x:hashlib.sha256(x).hexdigest()
DEC=Cs(CS_ARCH_PPC,CS_MODE_32|CS_MODE_BIG_ENDIAN)
def load(p):
 with open(p,'rb') as f:
  obj=ELFFile(f);st=obj.get_section_by_name('.symtab');fn=next(s for s in st.iter_symbols() if s.name==NAME);a=fn['st_value'];n=fn['st_size'];body=obj.get_section(fn['st_shndx']).data()[a:a+n];rels={}
  for sec in obj.iter_sections():
   if sec['sh_type'] not in ['SHT_REL','SHT_RELA'] or sec['sh_info']!=fn['st_shndx']:continue
   sy=obj.get_section(sec['sh_link'])
   for r in sec.iter_relocations():
    if a<=r['r_offset']<a+n:rels[r['r_offset']-a]=(r['r_info_type'],sy.get_symbol(r['r_info_sym']).name,r.entry.get('r_addend',0))
  return dict(raw=body,ins={i.address:(i.mnemonic,i.op_str) for i in DEC.disasm(body,0)},rels=rels)
B=load(args.baseline);C=load(args.candidate);T=load(args.original)
# Complete actual-body map: remove exactly the original negative-base li/b.
removed={0x664,0x668};mapped=lambda x:x-8 if x>=0x66c else x
changes=[]
for pc,(mn,op) in B['ins'].items():
 if pc in removed:continue
 cp=mapped(pc);cm,co=C['ins'][cp]
 if pc==0x660:assert (mn,op)==('bge','0x66c') and (cm,co)==('blt','0x678');changes.append(dict(baseline_offset=pc,candidate_offset=cp,old=[mn,op],new=[cm,co]));continue
 expected=op
 if mn.startswith('b') and mn!='blr':
  parts=op.split(', ');parts[-1]=hex(mapped(int(parts[-1],0)));expected=', '.join(parts)
 assert (cm,co)==(mn,expected),(hex(pc),(mn,op),(cm,co),expected)
for off,rel in B['rels'].items():assert C['rels'][mapped(off)]==rel,(off,rel)
assert len(C['ins'])==len(B['ins'])-2==506
# Exact unchanged load/call/operation order with only one branch inversion.
assert C['ins'][0x678]==('li','r24, 0') and C['ins'][0x67c]==('b','0x70c') and C['ins'][0x680]==('add.','r3, r21, r22')
assert T['ins'][0x690]==('li','r29, 0') and T['ins'][0x694]==('b','0x724') and T['ins'][0x698]==('add.','r3, r23, r22')

# Read the original DOL independently and verify target body + direct call destinations.
dol=args.dol.read_bytes();assert hashlib.sha1(dol).hexdigest()=='26116613f624061ba99c8d1a299aaa6efa85670d';word=lambda o:struct.unpack_from('>I',dol,o)[0]
sects=[(word(0x48+i*4),word(i*4),word(0x90+i*4)) for i in range(18)]
def at(a,n):
 for va,fo,size in sects:
  if va<=a and a+n<=va+size:return dol[fo+a-va:fo+a-va+n]
 raise AssertionError(('DOL address',hex(a),n))
syms={}
for line in args.symbols.read_text().splitlines():
 m=re.match(r'([^ ]+) = \.\w+:0x([0-9A-Fa-f]+);',line)
 if m:syms[m[1]]=int(m[2],16)
assert syms[NAME]==0x813d3424;nonrel=0;target_calls=[]
for pc in T['ins']:
 if not any(pc<=r<pc+4 for r in T['rels']):assert at(syms[NAME]+pc,4)==T['raw'][pc:pc+4];nonrel+=1
for pc,(typ,name,addend) in T['rels'].items():
 if typ!=10:continue
 w=int.from_bytes(at(syms[NAME]+pc,4),'big');d=w&0x3fffffc;d=d-0x4000000 if d&0x2000000 else d;assert (syms[NAME]+pc+d)&MASK==(syms[name]+addend)&MASK;target_calls.append(dict(offset=pc,name=name,destination=syms[name]+addend))
helpers={}
for name,start in [('_restgpr_20',20),('_restgpr_21',21)]:
 ins=[(i.mnemonic,i.op_str) for i in DEC.disasm(at(syms[name],4*(33-start)),0)];assert len(ins)==33-start
 for i,r in enumerate(range(start,32)):
  mm=re.fullmatch(r'r(\d+), (-?(?:0x[0-9a-f]+|[0-9]+))\(r11\)',ins[i][1]);assert mm and ins[i][0]=='lwz' and int(mm[1])==r and int(mm[2],0)==-4*(32-r)
 assert ins[-1][0]=='blr';helpers[name]=ins

GLOBAL=0x50000000;THREAD=0x10000000;THREAD2=0x10020000;SP=0x60000100;DIR=0x30000000;DST=0x40000000;RET=0x81234560
class Memory:
 def __init__(self):self.regions=[];self.trace=[]
 def add(self,a,n,data=None):self.regions.append((a,bytearray(data if data is not None else bytes(n))))
 def locate(self,a,n):
  assert a>=0 and n>=0
  for base,buf in self.regions:
   if base<=a and a+n<=base+len(buf):return buf,a-base
  raise AssertionError(('unallocated access',hex(a),n))
 def read(self,a,n,trace=True):
  b,i=self.locate(a,n);v=bytes(b[i:i+n]);
  if trace and not SP<=a<SP+0x100:self.trace.append(('read',a,n,v.hex()))
  return v
 def write(self,a,v,trace=True):
  b,i=self.locate(a,len(v));b[i:i+len(v)]=v
  if trace and not SP<=a<SP+0x100:self.trace.append(('write',a,len(v),v.hex()))
 def get(self,a,n=4,trace=True):return int.from_bytes(self.read(a,n,trace),'big')
 def put(self,a,v,n=4,trace=True):self.write(a,(v&((1<<(8*n))-1)).to_bytes(n,'big'),trace)
 def external(self):return [(a,bytes(b)) for a,b in self.regions if a!=SP]

def fixture(case):
 m=Memory();m.add(GLOBAL,4);m.add(THREAD,0xe000);m.add(THREAD2,0xe000);m.add(SP,0x100);m.add(DIR,0x80);m.add(DST,0x80)
 # Distinct deterministic initial comment streams and intact buffer guards.
 for t,k in [(THREAD,19),(THREAD2,73)]:
  m.write(t+0xd7c0,bytes((i*29+k)&255 for i in range(0x400)),False)
  dst=DST if case['alias']!=1 else t+0xdac0
  m.put(t+0xd3bc+case['slot']*0x1fc+case['file']*4,dst,trace=False)
 d=DIR
 if case['alias']==2:d=THREAD+0xdb00
 elif case['alias']==3:d=DST
 m.put(d+0x3c,case['address'],trace=False);m.put(d+0x38,case['length'],2,False);m.put(d+0x28,0xdec0ad12,trace=False);m.put(d+0x34,0x19,1,False)
 m.put(GLOBAL,THREAD,trace=False);m.put(SP+0x64,RET,trace=False)
 caller=[(0x9a000000+i*0x10203)&MASK for i in range(32)]
 for r in range(20,32):m.put(SP+0x60-4*(32-r),caller[r],trace=False)
 m.write(SP+0x10,bytes((i+7)&255 for i in range(0x14)),False)
 return m,d,caller

class Calls:
 def __init__(self,m,d,case):self.m=m;self.d=d;self.case=case;self.trace=[];self.count=0
 def mutate(self,where):
  p=self.case['callback']
  if (p==1 and where=='sector') or (p==2 and where=='read') or (p==3 and where=='close'):
   self.m.put(self.d+0x38,(self.case['length']+3)&0xffff,2);self.m.put(self.d+0x28,0xa5c3de19);self.m.put(self.d+0x34,0x02,1);self.m.put(self.d+0x3c,self.case['address']^0x12345678)
  if (p==4 and where=='sector') or (p==5 and where=='read'):self.m.put(GLOBAL,THREAD2)
 def call(self,name,args):
  m=self.m;c=self.case;self.count+=1;self.trace.append((name,tuple(args)));self.m.trace.append(('call',name,tuple(args)))
  if name=='CARDGetSectorSize':assert args==[c['slot'],SP+8];m.put(SP+8,c['sector']);self.mutate('sector');return c['get_result']&MASK
  if name=='CARDRead':
   assert args[0]==SP+0x10 and args[2] in [0x200,0x400] and args[3]%512==0;m.locate(args[1],args[2]);n=args[2] if c['read_result']>=0 else min(16,args[2]);m.write(args[1],bytes((i*17+31)&255 for i in range(n)));self.mutate('read');return c['read_result']&MASK
  if name=='memset':assert args[1]==0 and args[2]==64;m.write(args[0],bytes(args[2]));return args[0]
  if name=='memcpy':
   a,b,n=args;assert n==64 and (a+n<=b or b+n<=a),('memcpy overlap',args);v=m.read(b,n);m.write(a,v);return a
  if name=='CARDClose':assert args==[SP+0x10];self.mutate('close');return c['close_result']&MASK
  raise AssertionError(('call',name,args))

def mask(mb,me):return sum(1<<(31-i) for i in (range(mb,me+1) if mb<=me else list(range(mb,32))+list(range(0,me+1))))
def execute(obj,case,target=False):
 m,d,caller=fixture(case);hooks=Calls(m,d,case);r=caller.copy();r[1]=SP
 if target:r[24]=case['slot'];r[25]=case['file'];r[26]=d;r[27]=case['slot']*0x1fc;r[28]=case['file']*4;pc=0x644
 else:r[29]=case['slot'];r[30]=case['file'];r[31]=d;r[25]=case['slot']*0x1fc;r[26]=case['file']*4;pc=0x62c
 cr=0;lr=RET;coverage=set();steps=0
 def val(x):return r[int(x[1:])]
 def ea(op,offset):
  if offset in obj['rels']:
   typ,name,add=obj['rels'][offset];assert typ==109 and name=='sThread__Q23ipl10memorycard';return GLOBAL+add
  mt=re.fullmatch(r'(-?(?:0x[0-9a-f]+|\d+))\((r\d+|0)\)',op);assert mt,op;return ((0 if mt[2]=='0' else val(mt[2]))+int(mt[1],0))&MASK
 while True:
  steps+=1;assert steps<400;coverage.add(pc);mn,op=obj['ins'][pc];parts=op.split(', ');nxt=pc+4
  if mn in ['lwz','lhz','lbz']:r[int(parts[0][1:])]=m.get(ea(parts[1],pc),{'lwz':4,'lhz':2,'lbz':1}[mn])
  elif mn in ['stw','sth','stb']:m.put(ea(parts[1],pc),val(parts[0]),{'stw':4,'sth':2,'stb':1}[mn])
  elif mn=='mr':r[int(parts[0][1:])]=val(parts[1])
  elif mn=='li':r[int(parts[0][1:])]=int(parts[1],0)&MASK
  elif mn in ['addi','addis']:r[int(parts[0][1:])]=((0 if parts[1]=='0' else val(parts[1]))+(int(parts[2],0)<<(16 if mn=='addis' else 0)))&MASK
  elif mn in ['add','add.']:r[int(parts[0][1:])]=(val(parts[1])+val(parts[2]))&MASK;cr=(s32(r[int(parts[0][1:])])>0)-(s32(r[int(parts[0][1:])])<0) if mn=='add.' else cr
  elif mn=='subf':r[int(parts[0][1:])]=(val(parts[2])-val(parts[1]))&MASK
  elif mn=='mulli':r[int(parts[0][1:])]=(s32(val(parts[1]))*int(parts[2],0))&MASK
  elif mn=='mullw':r[int(parts[0][1:])]=(val(parts[1])*val(parts[2]))&MASK
  elif mn=='rlwinm':
   sh,mb,me=map(lambda x:int(x,0),parts[2:]);x=val(parts[1]);r[int(parts[0][1:])]=(((x<<sh)|(x>>(32-sh)))&mask(mb,me))&MASK
  elif mn=='xori':r[int(parts[0][1:])]=val(parts[1])^int(parts[2],0)
  elif mn=='cmpwi':x=s32(val(parts[0]));y=int(parts[1],0);cr=(x>y)-(x<y)
  elif mn=='cmplw':x=val(parts[0]);y=val(parts[1]);cr=(x>y)-(x<y)
  elif mn in ['b','blt','bge','ble','bgt','beq','bne']:
   take={'b':True,'blt':cr<0,'bge':cr>=0,'ble':cr<=0,'bgt':cr>0,'beq':cr==0,'bne':cr!=0}[mn]
   if take:nxt=int(parts[-1],0)
  elif mn=='bl':
   typ,name,add=obj['rels'][pc];assert typ==10 and add==0
   if name in helpers:
    for hm,ho in helpers[name][:-1]:hp=ho.split(', ');r[int(hp[0][1:])]=m.get(ea(hp[1],-1))
   else:
    arity=dict(CARDGetSectorSize=2,CARDRead=4,memset=3,memcpy=3,CARDClose=1)[name];result=hooks.call(name,r[3:3+arity])
    for k in [0,*range(3,13)]:r[k]=(0xb0000000+hooks.count*0x100+k)&MASK
    r[3]=result
  elif mn=='mtlr':lr=val(parts[0])
  elif mn=='blr':assert lr==RET and r[1]==SP+0x60;assert r[14:32]==caller[14:32],('nonvolatile GPR preservation',target);return dict(result=s32(r[3]),calls=hooks.trace,trace=m.trace,memory=m.external(),coverage=coverage,steps=steps)
  else:raise AssertionError(('unsupported instruction',hex(pc),mn,op))
  pc=nxt

def reference(case):
 m,d,caller=fixture(case);hooks=Calls(m,d,case);address=m.get(d+0x3c);base=address&0xfffffe00;offset=(address-base)&MASK;size=(((address+0x23f)&MASK)&0xfffffe00)-base;size&=MASK
 result=s32(hooks.call('CARDGetSectorSize',[case['slot'],SP+8]));clear=True
 if result>=0:
  if s32(base)<0:result=0
  else:
   fs=(m.get(d+0x38,2)*m.get(SP+8))&MASK
   if base>fs:result=0
   else:
    end=(base+size)&MASK
    if s32(end)<0 or end>fs:result=0
    else:
     t=m.get(GLOBAL);result=s32(hooks.call('CARDRead',[SP+0x10,t+0xd7c0,size,base]))
     if result>=0:
      t=m.get(GLOBAL);dest=m.get(t+0xd3bc+case['slot']*0x1fc+case['file']*4);hooks.call('memset',[dest,0,64]);t=m.get(GLOBAL);dest=m.get(t+0xd3bc+case['slot']*0x1fc+case['file']*4);hooks.call('memcpy',[dest,t+0xd7c0+offset,64]);result=0;clear=False
 if clear:t=m.get(GLOBAL);dest=m.get(t+0xd3bc+case['slot']*0x1fc+case['file']*4);hooks.call('memset',[dest,0,64])
 if result>=0:
  result=s32(hooks.call('CARDClose',[SP+0x10]))
  if result>=0:
   a=case['slot']*0x5f4+case['file']*12;t=m.get(GLOBAL);m.put(t+a+0x28,1,2);t=m.get(GLOBAL);length=m.get(d+0x38,2);m.put(t+a+0x2a,length,2);t=m.get(GLOBAL);key=m.get(d+0x28);m.put(t+a+0x30,key);permission=m.get(d+0x34,1);t=m.get(GLOBAL);m.put(t+a+0x2c,((permission>>3)&1)^1,1);permission=m.get(d+0x34,1);t=m.get(GLOBAL);m.put(t+a+0x2d,((permission>>4)&1)^1,1);result=0
 return dict(result=result,calls=hooks.trace,trace=m.trace,memory=m.external())

addresses=[0,1,0x1c0,0x1c1,0x1ff,0x200,0x201,0x3ff,0x400,0x7ffffbff,0x7ffffc00,0x7ffffdff,0x7ffffe00,0x7ffffe01,0x7fffffff,0x80000000,0x800001ff,0xfffffdc0,0xfffffe00,0xffffffff]
sectors=[0,1,0x200,0x400,0x2000,0x7fffffff,0x80000000,0xffffffff];lengths=[0,1,2,0xffff];cases=[]
def case(address=0x200,sector=0x2000,length=2,get_result=0,read_result=0,close_result=0,alias=0,callback=0,slot=0,file=0):return dict(address=address,sector=sector,length=length,get_result=get_result,read_result=read_result,close_result=close_result,alias=alias,callback=callback,slot=slot,file=file)
for i,(a,s,l) in enumerate(itertools.product(addresses,sectors,lengths)):cases.append(case(a,s,l,alias=i%4,callback=i%6,slot=i%2,file=[0,63,126][i%3]))
for a,g,rd,cl,al,cb in itertools.product([0x200,0x1ff,0x7ffffe01,0x80000000],[0,-3],[0,-7],[0,-10],range(4),range(6)):cases.append(case(a,get_result=g,read_result=rd,close_result=cl,alias=al,callback=cb,slot=al%2,file=[0,63,126][cb%3]))
rng=random.Random(202610032306)
for i in range(512):cases.append(case(rng.getrandbits(32),rng.getrandbits(32),rng.randrange(65536),get_result=rng.choice([0,0,0,-128]),read_result=rng.choice([0,-3]),close_result=rng.choice([0,-7]),alias=i%4,callback=i%6,slot=i%2,file=rng.choice([0,63,126])))
write('ppc-path-inputs.json',cases);coverage={n:set() for n in ['baseline','candidate','target']};dig=hashlib.sha256();counts={};start=time.time()
for number,x in enumerate(cases):
 rr=reference(x);objects=[('baseline',B,False),('candidate',C,False),('target',T,True)];result=[]
 for n,obj,is_target in objects:
  got=execute(obj,x,is_target)
  for k in ['result','calls','trace','memory']:assert got[k]==rr[k],('bounded path mismatch',number,n,k,x,got[k] if k not in ['memory','trace'] else 'see trace')
  coverage[n]|=got['coverage'];result.append((n,got['result'],got['calls'],sha(repr(got['trace']).encode()),sha(b''.join(v for _,v in got['memory']))))
 counts[str(rr['result'])]=counts.get(str(rr['result']),0)+1;dig.update(json.dumps([number,x,result],sort_keys=True).encode())
summary=dict(pass_all=True,cases=len(cases),actual_instruction_executions=3*len(cases),sequential_reference_executions=len(cases),seed=202610032306,case_sha256=sha((OUT/'ppc-path-inputs.json').read_bytes()),outcomes=counts,comparison_digest=dig.hexdigest(),coverage={n:sorted(v) for n,v in coverage.items()},coverage_counts={n:len(v) for n,v in coverage.items()},region_instruction_counts=dict(baseline=len([pc for pc in B['ins'] if pc>=0x62c]),candidate=len([pc for pc in C['ins'] if pc>=0x62c]),target=len([pc for pc in T['ins'] if pc>=0x644])),whole_body_mapping=dict(baseline=508,candidate=506,deleted_offsets=sorted(removed),changed_branch=changes,all506_remaining_actual_nodes_gpr_operands_and_relocations_mapped=True),target_shared_failure_and_valid_join_match=True,candidate_common_zero_offset=0x678,target_common_zero_offset=0x690,aliases=['disjoint objects','destination contained at commentBuffer+0x300; disjoint memcpy window','live descriptor contained at commentBuffer+0x340','destination equals allocated descriptor; source buffer disjoint'],callback_profiles=['none','sector mutates descriptor after commentAddr captured','read mutates descriptor','close mutates descriptor','sector replaces valid sThread','read replaces valid sThread'],all_memory_accesses_allocated=True,all_modeled_memcpy_ranges_nonoverlapping=True,all_source_reads_calls_writes_and_result_paths_equal=True,all_nonvolatile_gprs_stack_and_return_lr_preserved=True,original_dol_nonrelocated_words_checked=nonrel,original_dol_direct_calls=target_calls,actual_DOL_restore_helper_instructions=helpers,runtime_seconds=time.time()-start,limits='Fresh actual-instruction comment/return slice, entering with established live-ins from unchanged image prefix and preexisting saved frame. Modeled CARD/copy calls and valid allocated contained aliases. Does not execute image prefix, full SDK implementations or Wii hardware; no formal/all-input proof. Existing zero-icon negative-shift and reserved-format3 image-prefix limitations unchanged. Arbitrary sector/length bit-pattern cases are arithmetic robustness probes, not claims about physical cards.')
write('ppc-path-audit.json',summary);print('FRESH BOUNDED PPC PATH PASS',len(cases),'cases',3*len(cases),'actual executions; coverage',summary['coverage_counts'],'of',summary['region_instruction_counts'],flush=True)
