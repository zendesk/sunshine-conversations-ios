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

    SKTSettings* settings = [SKTSettings settingsWithAppToken:@""];
    settings.knowledgeBaseURL = SupportKitKnowledgeBaseURL;
    [SupportKit initWithSettings:settings];
    
    [SupportKit setDefaultRecommendations:@[
                                            @"https://supportkit.zendesk.com/hc/en-us/articles/201747860-Reporting-logs-to-your-support-team",
                                            @"https://supportkit.zendesk.com/hc/en-us/articles/201900704-Recommendations",
                                            @"https://supportkit.zendesk.com/hc/en-us/articles/201900224-Filtering-Search-Results-by-Category-or-Section",
                                            @"https://supportkit.zendesk.com/hc/en-us/articles/201616304-SKTSettings-What-do-they-do-",
                                            @"https://supportkit.zendesk.com/hc/en-us/articles/201626494-Custom-Event-track-API-Why-",
                                            ]];
    
    
    return YES;
}

@end
