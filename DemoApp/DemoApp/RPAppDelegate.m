//
//  RPAppDelegate.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/10/13.
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import "RPAppDelegate.h"
#import <SupportKit/SupportKit.h>
#import "RPZendeskPickerView.h"
#import "RPMainViewController.h"

@implementation RPAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    RPMainViewController* mainController = [[RPMainViewController alloc] init];

    self.window.rootViewController = mainController;
    [self.window makeKeyAndVisible];

    SKTSettings* settings = [SKTSettings settingsWithKnowledgeBaseURL:SupportKitKnowledgeBaseURL
                                                       andTicketURL:[SupportKitKnowledgeBaseURL stringByAppendingPathComponent:@"/hc/en-us/requests/new"]];
    [SupportKit initWithSettings:settings];
    
    return YES;
}

@end
