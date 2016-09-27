local ffi=require("ffi")
ffi.cdef[[
         int GMCommand(int argc,char **argv);
]]
local clib=ffi.load('GraphicsMagick')

local convert=function(args)
	if type(args)~="table" then
		return false,"error parameter format,require table"
	end
	local len=#args
	local len2=ffi.new("int",len)
 	local c_args=ffi.new("char*[?]",len)
 	for i=1,len,1  do
          local e=args[i]
          c_args[i-1]=ffi.cast("char *",e)
 	end
 	clib.GMCommand(len2,c_args)
 	return true,"success"
end

return {
   convert = convert,
}