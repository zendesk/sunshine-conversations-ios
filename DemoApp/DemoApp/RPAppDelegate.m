//
//  RPAppDelegate.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/10/13.
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import "RPAppDelegate.h"
#import "RPWelcomeViewController.h"

@implementation RPAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    RPWelcomeViewController* mainController = [[RPWelcomeViewController alloc] init];

    self.window.rootViewController = mainController;
    [self.window makeKeyAndVisible];
    
    return YES;
}

@end
