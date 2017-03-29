'''
        Programa auxiliar para generar las corridas del programa principal.
        
'''
from subprocess import check_output, call
import os
from glob import glob
import re


folders = glob("./Instances/*")


def func(path):
        stdout = open("{}".format(path+"-bb.txt"),"wb")
        call("bb.exe {}".format(path), stdout=stdout, shell=True)
        stdout.close()
        return 

def natural_sort(l): 
    convert = lambda text: int(text) if text.isdigit() else text.lower() 
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ] 
    return sorted(l, key = alphanum_key)

def limpiar():
        for f in folders:
                first = glob("{}/*.txt".format(f))
                for archivo in first:
                        os.remove(archivo)      


                
for f in folders:
	first = glob("{}/*".format(f))
	second = [ x for x in first if ".txt" not in x]
	print("Siguiente carpeta {}".format(f))
	for archivo in natural_sort(second):
		if not archivo+"-bb.txt" in first:
			print("Working on {}".format(archivo))
			func(archivo)
		else:
			print("Already computed,"+archivo+"-bb.txt")

