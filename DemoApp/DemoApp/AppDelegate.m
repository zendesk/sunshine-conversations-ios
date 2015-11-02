//
//  AppDelegate.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/10/13.
//  Copyright (c) 2015 Smooch Technologies. All rights reserved.
//

#import "AppDelegate.h"
#import <Smooch/Smooch.h>
#import "MainViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    MainViewController* mainController = [[MainViewController alloc] init];

    self.window.rootViewController = mainController;
    [self.window makeKeyAndVisible];

    //This is where you would put your token that was generated for your app on the Smooch console website.
    SKTSettings* settings = [SKTSettings settingsWithAppToken:@"4z6ruil9xi9kixnf4ezztf1kl"];
    settings.conversationAccentColor = [UIColor colorWithRed:145.0/255 green:45.0/255 blue:141.0/255 alpha:1.0];
    [Smooch initWithSettings:settings];
    
    [Smooch setUserFirstName:@"Demo" lastName:@"App"];
    
    return YES;
}

@end
