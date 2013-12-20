//
//  RPZendeskPickerView.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/19/13.
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import "RPZendeskPickerView.h"
#include <stdlib.h>

@interface RPZendeskPickerView()

@end


@implementation RPZendeskPickerView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self initializator];
    }
    return self;
}

-(void)initializator
{
    self.label = [[UILabel alloc] init];
    self.label.text = @"Want to see your knowledge base? Enter your Zendesk URL below and tap the Try It button!";
    self.label.backgroundColor = [UIColor clearColor];
    self.label.textAlignment = NSTextAlignmentCenter;
    self.label.font = [UIFont systemFontOfSize:14];
    self.label.numberOfLines = 0;
    
    [self addSubview:self.label];
    
    self.textField = [[UITextField alloc] init];
    self.textField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    self.textField.autocorrectionType = UITextAutocorrectionTypeNo;
    self.textField.borderStyle = UITextBorderStyleRoundedRect;
    self.textField.text = @"https://supportkit.zendesk.com";
    self.textField.backgroundColor = [UIColor whiteColor];
    self.textField.font = [UIFont systemFontOfSize:12];
    
    [self addSubview:self.textField];
    
    self.randomButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [self.randomButton setTitle:@"Random" forState:UIControlStateNormal];
    [self.randomButton addTarget:self action:@selector(randomizeURL) forControlEvents:UIControlEventTouchUpInside];
    
    [self addSubview:self.randomButton];
    
    self.button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [self.button setTitle:@"Try It" forState:UIControlStateNormal];
    
    [self addSubview:self.button];
}

-(void)layoutSubviews
{
    [super layoutSubviews];
    
    self.label.frame = CGRectMake(0, 75, self.bounds.size.width - 20, 500);
    [self.label sizeToFit];
    self.label.center = CGPointMake(CGRectGetMidX(self.bounds), self.label.center.y);
    
    self.textField.frame = CGRectMake(0, CGRectGetMaxY(self.label.frame) + 20, self.bounds.size.width - 20, 25);
    self.textField.center = CGPointMake(CGRectGetMidX(self.bounds), self.textField.center.y);
    
    self.randomButton.frame = CGRectMake(0, CGRectGetMaxY(self.textField.frame) + 15, 200, 35);
    [self.randomButton sizeToFit];
    self.randomButton.center = CGPointMake(CGRectGetMidX(self.bounds), self.randomButton.center.y);
    
    self.button.frame = CGRectMake(0, CGRectGetMaxY(self.randomButton.frame) + 15, 200, 35);
    [self.button sizeToFit];
    self.button.center = CGPointMake(CGRectGetMidX(self.bounds), self.button.center.y);
    
}

-(void)randomizeURL
{
    static NSArray* zendeskURLs;
    if(!zendeskURLs){
        zendeskURLs = @[
                        @"https://supportkit.zendesk.com",
                        @"https://fixmestick.zendesk.com",
                        @"https://prezi.zendesk.com",
                        @"https://mortgagecoach.zendesk.com",
                        @"https://topify.zendesk.com",
                        @"https://winshuttle.zendesk.com",
                        @"https://dyknow.zendesk.com",
                        @"https://picaboo.zendesk.com",
                        @"https://shootproof.zendesk.com",
                        @"https://huddle.zendesk.com",
                        @"https://streamtime.zendesk.com"
                       ];
    }
    
    int index;
    do{
        index = arc4random() % zendeskURLs.count;
    }
    while([self.textField.text isEqualToString:[zendeskURLs objectAtIndex:index]]);
            
    self.textField.text = zendeskURLs[index];
}

@end
