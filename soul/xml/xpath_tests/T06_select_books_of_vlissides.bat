@echo off
xpath_test -v "/library/objects/object[@kind='book'][./author[@objectID='john-vlissides'] or @id=/library/objects/object[@kind='group'][@id=/library/objects/object[@kind='person'][@id='john-vlissides']/groups/item/@objectID]/artworks/item/@objectID]/name" ../xml_test_data/library.xml
