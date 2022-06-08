@echo off
xpath_test -v "/library/objects/object[@kind='person'][@id=/library/objects/object[@kind='book'][@id='taocp']/author/@objectID]/name" ../xml_test_data/library.xml
