gm=require("convert")
local args={"convert","/Users/allan/Downloads/1.jpg","-thumbnail","300x300^"    ,"-gravity","center","-extent","300x300","/Users/allan/Downloads/3.jpg"}
gm.convert(args)
