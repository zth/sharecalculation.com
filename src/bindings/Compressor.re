module SafeBase64 = {
  [@bs.module "./base64"] external encode: string => string = "encode";
  [@bs.module "./base64"] external decode: string => string = "decode";
};

module LzString = {
  [@bs.module "./lzstring"] external encode: string => string = "compress";
  [@bs.module "./lzstring"] external decode: string => string = "decompress";
};

let compress = str => str |> LzString.encode |> SafeBase64.encode;
let decompress = str => str |> SafeBase64.decode |> LzString.decode;