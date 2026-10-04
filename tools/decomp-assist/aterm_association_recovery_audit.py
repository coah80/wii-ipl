"""Bounded actual PPC association-function executions versus sequential source reference.
No SDK implementation, hardware, formal or exhaustive MAC Cartesian proof.
"""
import sys
sys.dont_write_bytecode=True
from pathlib import Path
import hashlib,json,random,re,struct,itertools,time,os
from elftools.elf.elffile import ELFFile
from capstone import Cs,CS_ARCH_PPC,CS_MODE_32,CS_MODE_BIG_ENDIAN
import argparse
parser=argparse.ArgumentParser(description=__doc__)
for name in ['baseline','candidate','original','dol','symbols','output-dir']:parser.add_argument('--'+name,required=True,type=Path)
args=parser.parse_args()
NAME='ATERMBuildAssociationRequest'

OUT=args.output_dir.resolve();OUT.mkdir(parents=True,exist_ok=False)
def write(n,v):(OUT/n).write_text(json.dumps(v,indent=2)+'\n')

def plain(x):
 if hasattr(x,'items'):return {k:plain(v) for k,v in x.items()}
 if isinstance(x,(list,tuple)):return [plain(v) for v in x]
 return x

def metadata(path):
 with path.open('rb') as f:
  obj=ELFFile(f);sections=[dict(name=z.name,header=plain(z.header),data=z.data()) for z in obj.iter_sections()];symbols=[dict(name=z.name,entry=plain(z.entry)) for z in obj.get_section_by_name('.symtab').iter_symbols()];functions={}
  for z in obj.get_section_by_name('.symtab').iter_symbols():
   if z['st_info']['type']=='STT_FUNC' and isinstance(z['st_shndx'],int) and z['st_size']:
    sec=obj.get_section(z['st_shndx']);a=z['st_value'];n=z['st_size'];functions[z.name]=dict(section=sec.name,address=a,size=n,body=sec.data()[a:a+n])
  return dict(header=plain(obj.header),sections=sections,symbols=symbols,functions=functions)
mb=metadata(args.baseline);mc=metadata(args.candidate);assert mb['header']==mc['header'];assert len(mb['sections'])==len(mc['sections']);assert len(mb['symbols'])==len(mc['symbols'])==145;sectionchanges=[];pairs=[]
for b,c in zip(mb['sections'],mc['sections']):
 assert b['name']==c['name'] and b['header']==c['header']
 if b['data']!=c['data']:
  assert b['name'] in ['.text','.strtab'];sectionchanges.append(b['name'])
for i,(b,c) in enumerate(zip(mb['symbols'],mc['symbols'])):
 assert b['entry']==c['entry']
 if b['name']!=c['name']:
  ent=b['entry'];sec=mb['sections'][ent['st_shndx']];assert ent['st_info']==dict(bind='STB_LOCAL',type='STT_OBJECT');assert sec['data']==mc['sections'][ent['st_shndx']]['data'];extent=sec['data'][ent['st_value']:ent['st_value']+ent['st_size']];pairs.append(dict(index=i,old=b['name'],new=c['name'],entry=ent,section=sec['name'],extent_sha256=hashlib.sha256(extent).hexdigest()))
assert [(x['index'],x['old'],x['new']) for x in pairs]==[(22,'@2600','@2652'),(23,'@2652','@2704'),(24,'@1043','@1036'),(25,'@2792','@2844')]
assert mb['functions'].keys()==mc['functions'].keys();siblings=[]
for name,fn in mb['functions'].items():
 if name!=NAME:assert fn==mc['functions'][name];siblings.append(name)
assert len(siblings)==25
begin=mb['functions'][NAME]['address'];end=begin+mb['functions'][NAME]['size'];bt=next(z['data'] for z in mb['sections'] if z['name']=='.text');ct=next(z['data'] for z in mc['sections'] if z['name']=='.text');assert bt[:begin]==ct[:begin] and bt[end:]==ct[end:]
write('exact-metadata-audit.json',dict(pass_all=True,all_section_headers_symbol_entries_raw_relocation_tables_and_allocated_nontext_identical=True,all25_sibling_bodies_addresses_extents_identical=True,exact_four_local_name_pairs=pairs,section_data_changes=sectionchanges,no_broad_name_normalization=True))
MASK=0xffffffff;s32=lambda x:x-0x100000000 if x&0x80000000 else x
SD=0x20000000;SB=0x20010000;REQ=0x30000000;SP=0x60000100;FRAME=SP-0x60;RET=0x81234560
BASES={'.sdata':SD,'.sbss':SB}
DEC=Cs(CS_ARCH_PPC,CS_MODE_32|CS_MODE_BIG_ENDIAN)
def load(p):
 with open(p,'rb') as f:
  obj=ELFFile(f);st=obj.get_section_by_name('.symtab');fn=st.get_symbol_by_name(NAME)[0];a=fn['st_value'];n=fn['st_size'];body=obj.get_section(fn['st_shndx']).data()[a:a+n];rels={}
  for sec in obj.iter_sections():
   if sec['sh_type']!='SHT_RELA' or sec['sh_info']!=fn['st_shndx']:continue
   sy=obj.get_section(sec['sh_link'])
   for r in sec.iter_relocations():
    if a<=r['r_offset']<a+n:
     sm=sy.get_symbol(r['r_info_sym']);sid=sm['st_shndx'];at=r['r_offset']-a
     rels[at]=dict(type=r['r_info_type'],name=sm.name,addend=r['r_addend'],section=obj.get_section(sid).name if isinstance(sid,int) else sid,value=sm['st_value'])
  return dict(raw=body,ins={i.address:(i.mnemonic,i.op_str) for i in DEC.disasm(body,0)},rels=rels)
B=load(args.baseline);C=load(args.candidate);T=load(args.original)
assert len(B['ins'])==len(C['ins'])==len(T['ins'])==133
assert B['raw'][:0xc0]==C['raw'][:0xc0]==T['raw'][:0xc0]
assert B['raw'][0x1fc:]==C['raw'][0x1fc:]==T['raw'][0x1fc:]
assert B['rels']==C['rels']
for pc,z in B['rels'].items():
 target=T['rels'][pc];assert {k:v for k,v in z.items() if k!='name'}=={k:v for k,v in target.items() if k!='name'}
 if z['name']!=target['name']:
  assert (pc,z['name'],target['name'],z['section'],z['value']) in [(8,'gAtermProductName','lbl_81697248','.sdata',48),(0xb4,'gAtermUseSharedAddress','lbl_81697244','.sdata',44)]
# The candidate establishes both real six-iteration CTR loops at the target locations.
for pc in [0xc0,0xd8,0x154,0x15c,0x174,0x1f0]:assert C['ins'][pc]==T['ins'][pc]
assert B['ins'][0x14c][0]==B['ins'][0x1e8][0]=='cmplw'
assert B['ins'][0x154][0]==B['ins'][0x1f0][0]=='blt'
assert C['ins'][0x154][0]==C['ins'][0x1f0][0]=='bdnz'
# Exact dataflow-correspondence maps for the two inlined formatting regions.
# These explain residual operands only; they never alter scoring or compiled objects.
register_region_maps=[dict(begin=0xc0,end=0x158,mapping={9:5,5:9}),dict(begin=0x158,end=0x1fc,mapping={9:5,5:6,4:9,6:4})]
raw_operand_differences=[]
for pc,(mn,op) in C['ins'].items():
 target=T['ins'][pc];normalized=op
 for region in register_region_maps:
  if region['begin']<=pc<region['end']:
   normalized=re.sub(r'\br(\d+)\b',lambda mt:'r'+str(region['mapping'].get(int(mt[1]),int(mt[1]))),op)
 assert (mn,normalized)==target,(hex(pc),(mn,op),target)
 if (mn,op)!=target:raw_operand_differences.append(dict(offset=pc,candidate=[mn,op],target=list(target)))
assert len(raw_operand_differences)==28
write('actual-primitive-correspondence.json',dict(all133_mnemonics_immediates_branches_and_calls_correspond=True,remaining28_raw_differences=raw_operand_differences,exact_region_register_dataflow_maps=register_region_maps,no_scoring_normalization=True))
# Target words/direct-call addresses are independently verified against protected DOL.
dol=(args.dol).read_bytes();assert hashlib.sha1(dol).hexdigest()=='26116613f624061ba99c8d1a299aaa6efa85670d'
words=lambda o:struct.unpack_from('>18I',dol,o);sects=list(zip(words(0),words(0x48),words(0x90)))
def at(a,n):
 for fo,va,size in sects:
  if va<=a and a+n<=va+size:return dol[fo+a-va:fo+a-va+n]
 raise AssertionError(('DOL address',a,n))
syms={n:int(a,16) for n,a in re.findall(r'^([^\s=]+) = \.[^\s:]+:0x([0-9A-Fa-f]+);',(args.symbols).read_text(),re.M)}
raw=0;calls=[]
for pc in T['ins']:
 if pc not in T['rels']:assert at(syms[NAME]+pc,4)==T['raw'][pc:pc+4];raw+=1
for pc,rel in T['rels'].items():
 if rel['type']!=10:continue
 w=int.from_bytes(at(syms[NAME]+pc,4),'big');d=w&0x3fffffc;d-=0x4000000 if d&0x2000000 else 0;assert syms[NAME]+pc+d==syms[rel['name']]+rel['addend'];calls.append(dict(offset=pc,name=rel['name'],destination=syms[rel['name']]+rel['addend']))
class Memory:
 def __init__(self):self.regions=[];self.trace=[]
 def add(self,a,n,seed):self.regions.append((a,bytearray((seed+i*31)&255 for i in range(n))))
 def locate(self,a,n):
  for base,buf in self.regions:
   if base<=a and a+n<=base+len(buf):return buf,a-base
  raise AssertionError(('invalid allocation',hex(a),n))
 def read(self,a,n,trace=True):
  b,i=self.locate(a,n);v=bytes(b[i:i+n])
  if trace:self.trace.append(('read',a,n,v.hex()))
  return v
 def write(self,a,v,trace=True):
  b,i=self.locate(a,len(v));b[i:i+len(v)]=v
  if trace:self.trace.append(('write',a,len(v),v.hex()))
 def get(self,a,n=4,trace=True):return int.from_bytes(self.read(a,n,trace),'big')
 def put(self,a,v,n=4,trace=True):self.write(a,(v&((1<<(8*n))-1)).to_bytes(n,'big'),trace)
 def state(self):return [(a,bytes(b)) for a,b in self.regions]
def fixture(case):
 m=Memory();seed=case['seed'];m.add(SD,52,seed);m.add(SB,80,seed+71);m.add(REQ,32,seed+97);m.add(SP-0x100,0x180,seed+151)
 m.write(SD+48,b'WARP',False);m.put(SD+44,case['flag'],trace=False);m.write(SB+68,bytes.fromhex(case['scan']),False)
 request=[REQ,SB+48,SB+64,SD+32][case['alias']];m.locate(request,16)
 caller=[((0x91000000+i*0x12345)^seed)&MASK for i in range(32)];caller[1]=SP;caller[3]=request
 return m,request,caller
class Hooks:
 def __init__(self,m,req,case):self.m=m;self.req=req;self.case=case;self.trace=[];self.count=0;self.cmp_sign=None
 def call(self,name,args):
  self.count+=1;self.trace.append((name,tuple(args)));self.m.trace.append(('call',name,tuple(args)));m=self.m;c=self.case
  if name=='memcpy':
   dst,src,n=args;assert dst+n<=src or src+n<=dst,('overlapping memcpy forbidden',args);v=m.read(src,n);m.write(dst,v);return dst
  if name=='memcmp':
   aa,bb,n=args;assert n==6
   for i in range(n):
    a=m.get(aa+i,1);b=m.get(bb+i,1)
    if a!=b:self.cmp_sign=(a>b)-(a<b);return (a-b)&MASK
   self.cmp_sign=0;return 0
  if name=='NCDGetWirelessMacAddress':
   assert args==[FRAME+8];m.write(args[0],bytes.fromhex(c['interface']));profile=c['callback']
   if profile==1:
    m.write(SB+68,bytes((c['seed']+i*19)&255 for i in range(6)));m.write(SD+48,b'NEC!');m.put(SD+44,0)
   elif profile==2:
    m.write(self.req,bytes((c['seed']+i*29)&255 for i in range(16)));m.write(SB+68,bytes((c['seed']+i*23)&255 for i in range(6)));m.put(SD+44,0xffffffff)
   elif profile==3:
    value=m.get(SD+44);m.put(SD+44,value^1);m.write(SB+56,b'MUTATE');m.put(self.req+2,(c['seed']^0x95)&255,1)
   return c['ncd_return']&MASK
  raise AssertionError(('unknown call',name,args))
def mask(mb,me):return sum(1<<(31-i) for i in (range(mb,me+1) if mb<=me else list(range(mb,32))+list(range(0,me+1))))
def execute(obj,case):
 m,req,caller=fixture(case);hooks=Hooks(m,req,case);r=caller.copy();pc=0;cr=0;ctr=case['seed']&MASK;lr=RET;coverage=set();steps=0
 def val(x):return r[int(x[1:])]
 def reladdr(pc):
  z=obj['rels'][pc];assert z['type']==109 and z['section'] in BASES;return BASES[z['section']]+z['value']+z['addend']
 def ea(op,pc):
  if pc in obj['rels']:return reladdr(pc)
  mt=re.fullmatch(r'(-?(?:0x[0-9a-f]+|\d+))\((r\d+|0)\)',op);assert mt,op;return ((0 if mt[2]=='0' else val(mt[2]))+int(mt[1],0))&MASK
 while True:
  steps+=1;assert steps<1000;coverage.add(pc);mn,op=obj['ins'][pc];pp=op.split(', ');nxt=pc+4
  if mn in ['lwz','lbz']:r[int(pp[0][1:])]=m.get(ea(pp[1],pc),4 if mn=='lwz' else 1)
  elif mn in ['stw','stb']:m.put(ea(pp[1],pc),val(pp[0]),4 if mn=='stw' else 1)
  elif mn=='stwu':addr=ea(pp[1],pc);m.put(addr,val(pp[0]));r[1]=addr
  elif mn=='mflr':r[int(pp[0][1:])]=lr
  elif mn=='mtlr':lr=val(pp[0])
  elif mn=='mtctr':ctr=val(pp[0])
  elif mn=='mr':r[int(pp[0][1:])]=val(pp[1])
  elif mn=='li':r[int(pp[0][1:])]=reladdr(pc) if pc in obj['rels'] else int(pp[1],0)&MASK
  elif mn=='addi':r[int(pp[0][1:])]=((0 if pp[1]=='0' else val(pp[1]))+int(pp[2],0))&MASK
  elif mn=='add':r[int(pp[0][1:])]=(val(pp[1])+val(pp[2]))&MASK
  elif mn=='subf':r[int(pp[0][1:])]=(val(pp[2])-val(pp[1]))&MASK
  elif mn=='andi.':r[int(pp[0][1:])]=val(pp[1])&int(pp[2],0);v=r[int(pp[0][1:])];cr=(s32(v)>0)-(s32(v)<0)
  elif mn=='rlwinm':sh,mb,me=map(lambda x:int(x,0),pp[2:]);x=val(pp[1]);r[int(pp[0][1:])]=(((x<<sh)|(x>>(32-sh)))&mask(mb,me))&MASK
  elif mn=='clrlwi':r[int(pp[0][1:])]=val(pp[1])&((1<<(32-int(pp[2],0)))-1)
  elif mn=='cmpwi':x=s32(val(pp[0]));y=int(pp[1],0);cr=(x>y)-(x<y)
  elif mn=='cmplw':x=val(pp[0]);y=val(pp[1]);cr=(x>y)-(x<y)
  elif mn in ['b','beq','bgt','bge','blt']:
   take={'b':True,'beq':cr==0,'bgt':cr>0,'bge':cr>=0,'blt':cr<0}[mn]
   if take:nxt=int(pp[-1],0)
  elif mn=='bdnz':ctr=(ctr-1)&MASK;nxt=int(pp[0],0) if ctr else nxt
  elif mn=='bl':
   rel=obj['rels'][pc];assert rel['type']==10 and rel['addend']==0;name=rel['name'];arity=1 if name=='NCDGetWirelessMacAddress' else 3;result=hooks.call(name,r[3:3+arity]);lr=nxt
   for k in [0,*range(3,13)]:r[k]=(0xb0000000+hooks.count*0x100+k+case['seed'])&MASK
   ctr=(0xc0000000+hooks.count+case['seed'])&MASK;cr=1;r[3]=result
  elif mn=='blr':
   assert lr==RET and r[1]==SP and r[14:32]==caller[14:32];return dict(result=r[3],calls=hooks.trace,trace=m.trace,memory=m.state(),coverage=coverage,steps=steps,cmp_sign=hooks.cmp_sign)
  else:raise AssertionError(('unsupported actual instruction',hex(pc),mn,op))
  pc=nxt

def reference(case):
 m,req,caller=fixture(case);hooks=Hooks(m,req,case);m.put(FRAME,SP);m.put(FRAME+0x64,RET);m.put(FRAME+0x5c,caller[31]);hooks.call('memcpy',[req+12,SD+48,4]);hooks.call('memcpy',[FRAME+0x10,SB+68,6]);v=m.get(FRAME+0x10,1);m.put(FRAME+0x10,v&0xfd,1);hooks.call('NCDGetWirelessMacAddress',[FRAME+8]);hooks.call('memcpy',[SB+56,FRAME+8,6]);order=s32(hooks.call('memcmp',[FRAME+0x10,FRAME+8,6]))
 if order<=0:hooks.call('memcpy',[req,FRAME+8,6]);hooks.call('memcpy',[req+6,FRAME+0x10,6])
 else:hooks.call('memcpy',[req,FRAME+0x10,6]);hooks.call('memcpy',[req+6,FRAME+8,6])
 flag=m.get(SD+44)
 if flag:
  for inp,out in [(FRAME+8,FRAME+0x38),(FRAME+0x10,FRAME+0x18)]:
   cursor=out
   for i in range(6):
    byte=m.get(inp+i,1);hi=byte//16;lo=byte%16;m.put(cursor,hi+(48 if hi<=9 else 55),1);m.put(cursor+1,lo+(48 if lo<=9 else 55),1);m.put(cursor+2,0,1);cursor+=2
    if i<5:m.put(cursor,58,1);cursor+=1
   m.put(cursor,0,1)
 m.get(FRAME+0x5c);m.get(FRAME+0x64);return dict(result=1,calls=hooks.trace,trace=m.trace,memory=m.state(),cmp_sign=hooks.cmp_sign,formatting=bool(flag))

def case(scan,interface,flag=1,alias=0,callback=0,seed=0,ncd_return=0):return dict(scan=bytes(scan).hex(),interface=bytes(interface).hex(),flag=flag,alias=alias,callback=callback,seed=seed,ncd_return=ncd_return)
cases=[]
# Exhaust all256 raw input byte values independently at all six positions of both actual source arrays.
for value,pos,which in itertools.product(range(256),range(6),range(2)):
 scan=[0x5a]*6;interface=[0xa5]*6
 (scan if which==0 else interface)[pos]=value;cases.append(case(scan,interface,seed=len(cases)))
patterns=[bytes(6),bytes([255]*6),bytes(range(6)),bytes(range(5,-1,-1)),bytes([9,10,0x99,0x9a,0xa0,0xfa]),bytes([0x10,0xef,0xfe,0xa9,0x90,0x0f]),bytes([0,1,2,0xff,0x7f,0x80]),bytes([0x80,0x7f,0xff,2,1,0])]
for a,b,alias,cb,flag in itertools.product(patterns,patterns,range(4),range(4),[0,1,0xffffffff]):cases.append(case(a,b,flag,alias,cb,len(cases),[-5,0,1,-1][cb]))
rng=random.Random(202610040007)
for i in range(512):cases.append(case(rng.randbytes(6),rng.randbytes(6),rng.choice([0,1,0xffffffff,0x80000000]),i%4,i%4,len(cases),rng.choice([-5,-1,0,1])))
assert len(cases)==6656;write('ppc-path-inputs.json',cases)
coverage={n:set() for n in ['baseline','candidate','target']};digest=hashlib.sha256();counts={};start=time.time();maxsteps=0
for number,x in enumerate(cases):
 rr=reference(x)
 for n,obj in [('baseline',B),('candidate',C),('target',T)]:
  got=execute(obj,x)
  for k in ['result','calls','trace','memory','cmp_sign']:assert got[k]==rr[k],('bounded mismatch',number,n,k,x,got[k] if k in ['result','cmp_sign'] else 'trace/state')
  coverage[n].update(got['coverage']);maxsteps=max(maxsteps,got['steps'])
 counts[str((x['alias'],x['callback'],rr['formatting'],rr['cmp_sign']))]=counts.get(str((x['alias'],x['callback'],rr['formatting'],rr['cmp_sign'])),0)+1
 digest.update(json.dumps(x,sort_keys=True).encode());digest.update(repr(rr['trace']).encode());digest.update(repr(rr['memory']).encode())
for n,obj in [('baseline',B),('candidate',C),('target',T)]:assert coverage[n]==set(obj['ins']),('coverage',n,set(obj['ins'])-coverage[n])
summary=dict(pass_all=True,cases=len(cases),actual_ppc_executions=len(cases)*3,independent_sequential_reference_executions=len(cases),all256_raw_input_byte_values_at_every_six_positions_of_both_input_arrays=True,selected_bssid_first_byte_bit1_is_cleared_as_existing_source_requires=True,actual_return_calls_ordered_full_memory_read_write_trace_and_all_allocated_state_equal=True,all_nonvolatile_registers_stack_and_return_address_preserved=True,coverage={n:dict(covered=len(v),total=133,offsets=sorted(v)) for n,v in coverage.items()},caller_alias_layouts=['disjoint request','request inside sbss overlapping addressBuffer','request inside sbss overlapping selectedBssid','request inside sdata overlapping shared-address flag'],callback_profiles=['valid MAC output','also mutate selected/product/flagzero','also mutate request/selected/flagffffffff','also mutate request/addressBuffer/toggleflag'],ncd_returns=[-5,-1,0,1],all_memcpy_ranges_allocated_and_nonoverlapping=True,actual_cfg_loop_primitives_fixed=True,target_dol_nonrelocated_words_verified=raw,target_direct_calls_verified=calls,max_actual_steps=maxsteps,result_digest=digest.hexdigest(),case_classes=counts,elapsed_seconds=time.time()-start,limits=['Bounded whole-function actual-object PPC interpreter and independent sequential reference; not hardware or formal proof','memcpy/memcmp/NCD external routines modeled to their stated valid-buffer contracts rather than executing all SDK internals','All ELF relocations retain their actual section/symbol/addend semantics, rebased to private allocated model regions','Private caller frame and concrete four valid request/global contained-alias layouts, four NCD callback profiles; not arbitrary invalid pointers or out-of-bounds callback writes','Every byte value separately at every input position plus structured MAC pairs and512 deterministic random pairs; not exhaustive2^96 pair domain','NCD error-return probes still provide six initialized output bytes; source behavior after an NCD failure leaving bytes unwritten is not exploited or newly defined','Formatting writes remain in existing private arrays even though no C consumer follows; no new dummy output storage'],no_formal_or_hardware_claim=True)
write('ppc-path-audit.json',summary);print('PPC REFERENCE PASS',len(cases),'cases',len(cases)*3,'actualexec full133/133 allthree;exactcalls/readwrites/allocatedstate',flush=True)
