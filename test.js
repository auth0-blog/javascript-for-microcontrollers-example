var s = photon.TCPClient();
photon.log.trace('1');
photon.log.trace(s.connect('i5-4590-LIN', 3000));
photon.log.trace('2');
s.write('Hello from JS!');
photon.log.trace('3');
while(s.connected()) {
    photon.process();

    if(s.available()) {
        photon.log.trace(s.read());
    }
}
photon.log.trace('5');
s.stop();
photon.log.trace('4');
