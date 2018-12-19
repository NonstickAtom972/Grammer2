class uint8:
  def __init__(self,x):
    self.x=int(x)&255
  def __call__(self):
    return self.x
  def __str__(self):
    return str(self.x)
  def __add__(self,a):
    self.x=(self.x+int(a))&255
  def __add__(self,a):
    self.x=(self.x+int(a))&255
  def __sub__(self,a):
    self.x=(self.x-int(a))&255
class Float:
  def __init__(self,x):
    e=128
    self.s=0
    if x<0:
      self.s=1
      x=-x
    if x==0:
      self.m=x
      self.e=uint8(0)
      return
    while x<1:
      x*=2
      e-=1
    while x>=2:
      x*=.5
      e+=1
    self.e=uint8(e)
    self.m=int(x*2**31+.5)
  def __call__(self):
    x=self.m*(2**(self.e.x-128-31))
    if self.s==0:
      return x
    return -x
  def __str__(self):
    return "2^"+str(self.e.x-128)+" * "+str(self.m*2**-31)
def sqrt(n):
  r=0
  b=0x8000
  while b>0:
    b/=2
    if n-r-b>=0:
      n = n-r-b;
      r=r+b+b;
    r/=2
    b/=2
  return [r,n]
def sqrt16(DE):
  HL=0
  BC=0x8000
  while BC>0:
    BC/=2
    if DE-HL-BC>=0:
      DE = DE-HL-BC;
      HL=HL+BC+BC;
    HL/=2
    BC/=2
  return [HL,DE]
def div_16_8(n,d):
  y=n/d
  return [y,n-y*d]
def sqrt32(x):
  y=Float(x)
  z=sqrt16(y.m>>16)
  a=(z[1]<<8)|((y.m>>8)&255)
  x=z[0]
  b=div_16_8(a,x+x)
  a=(b[1]<<8)|(y.m&255)-b[0]*b[0]
  x=(x<<8)+b[0]
  b=(a<<16)/(x+x)
  x=(x<<16)+b
  l=[]
  while x>0:
    l=[x&255]+l
    x>>=8
  print(l)
  return x
print(sqrt(16))
print(sqrt(17))
print(sqrt(15))
print(sqrt(34657))
print(sqrt32(3.14159265358979))
print([226,223,196,141.85712784])