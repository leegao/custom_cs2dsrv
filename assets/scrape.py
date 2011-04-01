import urllib2, urllib
from BeautifulSoup import BeautifulSoup
import re

import pickle, glob

def ls(filename, dir):
    return dir+"\\"+filename in glob.glob(dir+'/*')

class memoize(object):
    def __init__(self, func):
        self.func = func
        self.name = func.func_name
        if ls(self.name, "memoize"):
            _f = open("memoize/"+self.name, "r")
            self.cache = pickle.load(_f)
            _f.close()
        else:
            self.cache = {}
    def __call__(self, *args):
        try:
            obj = self.cache[args]
            if not obj: self.cache[None]
            #if isinstance(obj, str): self.cache[None]
            return obj
        except KeyError:
            self.cache[args]=value=self.func(*args)
            _f = open("memoize/"+self.name,"w")
            pickle.dump(self.cache, _f)
            _f.close()
            return value
        except TypeError:
            return self.func(*args)
        

def _url(cmd = "", cat="all"):
    return "http://cs2d.com/help.php?"+urllib.urlencode({"cmd":cmd,"cat":cat})

def _get(url):
    return urllib2.urlopen(url).read()

def get(cmd="",cat="all"):
    return _get(_url(cmd,cat))


@memoize
def get_all(cat = "all"):
    soup = BeautifulSoup(get(cat = cat))
    all = soup.html.body.findAll('h3')[1].nextSibling.table.tr.findAll('a')
    #all.pop(0)
    return [element.string for element in all]
@memoize
def command(cmd, cat="all"):
    strip = re.compile("<.+?>")
    soup = BeautifulSoup(get(cmd, cat))
    cmd = soup.findAll(name='h1',text=cmd)[1].next
    categories = cmd.findAll("h3")[0].nextSibling.nextSibling.string.split(",")
    
    params = cmd.findAll("h3")[1]
    everything = params.findNextSiblings(**{"class":"inner"})
    info = strip.sub("",str(everything.pop().renderContents()))
    
    iparams = []
    
    for thing in everything:
        iparams.append(strip.sub("",str(thing.contents[0])).strip())
    
    return categories, info, iparams
        
def pretty(cmd, categories, parameters, info, iparams):
    print "\n%s"%cmd.title()
    print "+----------------------------------"
    print "| Categories: %s"%", ".join(categories)
    if parameters:
        print "| Parameters: %s"%", ".join(["<"+key+">" for key in iparams])
    print "| Info: %s"%info.replace("\n", "|    ").replace("<br />", "")
    print "+----------------------------------"

def luafy(cmd, categories, info, params):
    pass

import textwrap, sys
sys.stdout = open("add.lua", "w")

lol = r"""a = a .. "\n" .. generate("%s", "%s", %s, %s)"""

print "parsehelp = {}"
all = get_all("server")
for thing in all:
	cat,info,params = command(thing)
	
	params_ = [par.split()[0] for par in params if par != "none"]
	n = len(params_)
	fmt = ["i"]*n
	for i,par in enumerate(params_):
		par = par.replace(" ", "_")
		if "[" in par:
			n-=1
			par = par.replace("[","").replace("]","")
		params_[i] = par
		p2 = params[i]
		if "(text)" in p2: fmt[i] = "s"
	if params_:
		p = ", ".join(['"'+par+'"' for par in params_])
	else:
		p = "nil"
	print lol%(thing, "".join(fmt), n, p)
    # print "parsehelp.%s=[["%thing
    # print "    +---------------------------------------------------"
    # cat,info,params = command(thing)
    # params = [param.replace("player","other") for param in params if param != "none"]
    # if params:
        # print "    |", "Parameters:"
        # for param in params:
            # print "    |",param
        # print "    |"
    # print "    | Description"
    # infos = ["\n    | ".join(textwrap.wrap(i.strip(),50)) for i in info.split("\n") if i.strip()]
    # print "    |   "+"\n    |   ".join(infos)
    # print "    +---------------------------------------------------"
    # print "]]"