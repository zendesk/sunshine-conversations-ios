//
//  AppDelegate.m
//  DemoApp
//
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

    // Below is where you would put your app's ios-sdk integrationId;
    // Find it on the Sunshine Conversations dashboard, or via API: https://docs.smooch.io/rest/#get-sdk-ids
    SKTSettings *settings = [SKTSettings settingsWithIntegrationId: @"59aad4616082d43a0050a967"];
    settings.conversationAccentColor = [UIColor colorWithRed:145.0/255 green:45.0/255 blue:141.0/255 alpha:1.0];
    [Smooch initWithSettings:settings completionHandler:nil];

    [Smooch setUserFirstName:@"Demo" lastName:@"App"];

    return YES;
}

@end
