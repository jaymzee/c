wavefmt - read and write wav files
----------------------------------
For writing filters, it's most efficient to stream the data itself on the fly,
rather than allocating memory for it, so only the header is implemented here.

Note: to simplify the implementation, this assumes a little endian machine
which is pretty much any of the major platforms anyone would probably use
with this anyway.
