@echo off
xpath_test -v "/child::processing-instruction() | /root/child::processing-instruction()" ../xml_test_data/pi.xml
