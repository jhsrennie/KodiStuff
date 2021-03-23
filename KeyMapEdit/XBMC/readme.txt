To try and keep ShowKey in sync with developments in XBMC, this
directory contains XBMC source files copied from the XBMC repository.

The files have had minor editing to remove unwanted includes and the
like, but are similar enough to the originals to make it easy to
update them to keep up with future changes.

The only calls to code in this directory are made from the
GetXBMCKeyname function in MsgUtils.cpp.
