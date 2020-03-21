// Utils.h
// @author: Ian Torres <iantorres@outlook.com>

String ipAddressToStr(const IPAddress& address){
  return String() + address[0] + "." + address[1] + "." + address[2] + "." + address[3];
}
