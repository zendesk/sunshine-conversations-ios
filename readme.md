# [Smooch](http://www.smooch.io)

[![Pod Version](http://img.shields.io/cocoapods/v/Smooch.svg)](http://cocoadocs.org/docsets/Smooch/)
[![Platform](http://img.shields.io/cocoapods/p/Smooch.svg)](http://cocoadocs.org/docsets/Smooch/)
[![License](http://img.shields.io/cocoapods/l/Smooch.svg)](http://smooch.io/terms.html)
[![Carthage compatible](https://img.shields.io/badge/Carthage-compatible-4BC51D.svg?style=flat)](https://github.com/Carthage/Carthage)

Sign up and get an app token: [https://app.smooch.io/signup](https://app.smooch.io/signup).

CocoaPods:

    pod 'Smooch'
    pod update

Carthage:

    github "smooch/smooch-ios"
    carthage update

Obj-C:

```objc
[Smooch initWithSettings:[SKTSettings settingsWithAppToken:@"YOURAPPTOKEN"]];
[Smooch show];
```
    
Swift:

In your bridging header:

```objc
#import <Smooch/Smooch.h>
```
    
In a Swift file:

```Swift
Smooch.initWithSettings(SKTSettings(appToken: "YOUR_APP_TOKEN"))
Smooch.show()
```

Our [Docs and full install guide](http://docs.smooch.io).

Also, check out [Smooch Help Kit](https://github.com/smooch/smooch-helpkit-ios) for even more features!