fwrapdata
=========

Provide stream access to a CFMutableData structure.

It is possible to access the underlying data concurrently with stdio
functions, CFData/CFMutableData functions, and NSData/NSMutableData
methods. Direct access to the underlying data does not change the stream
position (it may be desirable to fseek() after adding or changing bytes).

fclose() must eventually be called on the returned handle to liberate
internally allocated memory.

