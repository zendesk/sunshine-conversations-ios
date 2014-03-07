//
//  RPZendeskPickerView.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/19/13.
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import "RPZendeskPickerView.h"
#import <stdlib.h>
#import "RPRoundedButton.h"

NSString* const SupportKitKnowledgeBaseURL = @"https://supportkit.zendesk.com";

@interface RPZendeskPickerView()

@property UILabel* label;
@property UIButton* randomButton;

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
    [self initLabel];
    [self initTextField];
    [self initRandomButton];
    [self initLaunchButton];
    [self initShowGestureHintButton];
    
    [self addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self.textField action:@selector(resignFirstResponder)]];
}

-(void)initLabel
{
    self.label = [[UILabel alloc] init];
    self.label.text = @"To see your knowledge base content, enter your Zendesk URL below and launch help.";
    self.label.backgroundColor = [UIColor clearColor];
    self.label.textAlignment = NSTextAlignmentCenter;
    self.label.font = [UIFont systemFontOfSize:14];
    self.label.numberOfLines = 0;
    self.label.textColor = [UIColor whiteColor];
    
    [self addSubview:self.label];
}

-(void)initTextField
{
    self.textField = [[UITextField alloc] init];
    self.textField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    self.textField.autocorrectionType = UITextAutocorrectionTypeNo;
    self.textField.borderStyle = UITextBorderStyleRoundedRect;
    self.textField.text = SupportKitKnowledgeBaseURL;
    self.textField.backgroundColor = [UIColor whiteColor];
    self.textField.font = [UIFont systemFontOfSize:14];
    
    [self addSubview:self.textField];
}

-(void)initRandomButton
{
    self.randomButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [self.randomButton setTitle:@"Random" forState:UIControlStateNormal];
    [self.randomButton.titleLabel setFont:[UIFont systemFontOfSize:15]];
    self.randomButton.tintColor = [UIColor whiteColor];
    
    [self.randomButton addTarget:self action:@selector(randomizeURL) forControlEvents:UIControlEventTouchUpInside];
    
    [self addSubview:self.randomButton];
}

-(void)initLaunchButton
{
    self.launchButton = [[RPRoundedButton alloc] initWithFrame:CGRectZero cornerRadius:12];
    [self.launchButton setTitle:@"Launch" forState:UIControlStateNormal];
    [self.launchButton.titleLabel setFont:[UIFont systemFontOfSize:15]];
    
    [self addSubview:self.launchButton];
}

-(void)initShowGestureHintButton
{
    self.showGestureHintButton = [RPRoundedButton new];
    [self.showGestureHintButton setTitle:@"Show Gesture Hint" forState:UIControlStateNormal];
    [self.showGestureHintButton.titleLabel setFont:[UIFont systemFontOfSize:15]];
    
    [self addSubview:self.showGestureHintButton];
}

-(void)layoutSubviews
{
    [super layoutSubviews];
    
    self.label.frame = CGRectMake(0, 40, self.bounds.size.width - 20, 500);
    [self.label sizeToFit];
    self.label.center = CGPointMake(floor(CGRectGetMidX(self.bounds)), self.label.center.y);
    
    self.textField.frame = CGRectMake(0, CGRectGetMaxY(self.label.frame) + 20, self.bounds.size.width - 20, 30);
    self.textField.center = CGPointMake(floor(CGRectGetMidX(self.bounds)), self.textField.center.y);
    
    self.randomButton.frame = CGRectMake(self.textField.frame.origin.x + 5, CGRectGetMaxY(self.textField.frame) + 10, 200, 25);
    [self.randomButton sizeToFit];
    
    self.launchButton.frame = CGRectMake(self.bounds.size.width - 110, 0, 100, 25);
    self.launchButton.center = CGPointMake(self.launchButton.center.x, self.randomButton.center.y);
    
    self.showGestureHintButton.frame = CGRectMake(0, CGRectGetMaxY(self.frame) - 70, 200, 46);
    [self.showGestureHintButton sizeToFit];
    self.showGestureHintButton.center = CGPointMake(floor(CGRectGetMidX(self.bounds)), self.showGestureHintButton.center.y);
}

-(void)randomizeURL
{
    static NSArray* zendeskURLs;
    if(!zendeskURLs){
        zendeskURLs = @[
                        SupportKitKnowledgeBaseURL,
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
    } while([self.textField.text isEqualToString:[zendeskURLs objectAtIndex:index]]);
            
    self.textField.text = zendeskURLs[index];
}

@end
