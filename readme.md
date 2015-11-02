# [Smooch](http://www.smooch.io)

[![Pod Version](http://img.shields.io/cocoapods/v/Smooch.svg)](http://cocoadocs.org/docsets/Smooch/)
[![Platform](http://img.shields.io/cocoapods/p/Smooch.svg)](http://cocoadocs.org/docsets/Smooch/)
[![License](http://img.shields.io/cocoapods/l/Smooch.svg)](http://smooch.io/terms.html)

Sign up and get an app token: [https://app.smooch.io/signup](https://app.smooch.io/signup).

CocoaPods:

    pod 'Smooch'
    pod update
    
Obj-C:
    
    [Smooch initWithSettings:[SKTSettings settingsWithAppToken:@"YOURAPPTOKEN"]];
    [Smooch show];
    
Swift:

    Smooch.initWithSettings("YOURAPPTOKEN")
    Smooch.show()

Our [Docs and full install guide](http://docs.smooch.io).

Also, check out [Smooch Help Kit](https://github.com/smooch/smooch-helpkit-ios) for even more features!