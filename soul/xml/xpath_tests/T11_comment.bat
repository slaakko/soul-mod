@echo off
xpath_test -v "/child::comment() | /root/child::comment()" ../xml_test_data/comments.xml
