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
#import "RPAppDelegate.h"

@interface RPZendeskPickerView()

@property UILabel* label;

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
    [self initLaunchButton];
    [self initShowGestureHintButton];
    
    [self addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self.textField action:@selector(resignFirstResponder)]];
}

-(void)initLabel
{
    self.label = [[UILabel alloc] init];
    self.label.text = @"To see your knowledge base content, change the code in RPAppDelegate to use your own Zendesk URL.";
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
    self.textField.text = KnowledgeBaseURL;
    self.textField.backgroundColor = [UIColor whiteColor];
    self.textField.font = [UIFont systemFontOfSize:14];
    [self.textField setEnabled:NO];
    
    [self addSubview:self.textField];
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
    
    self.launchButton.frame = CGRectMake(self.bounds.size.width - 110, CGRectGetMaxY(self.textField.frame) + 10, 100, 25);
    
    self.showGestureHintButton.frame = CGRectMake(0, CGRectGetMaxY(self.frame) - 70, 200, 46);
    [self.showGestureHintButton sizeToFit];
    self.showGestureHintButton.center = CGPointMake(floor(CGRectGetMidX(self.bounds)), self.showGestureHintButton.center.y);
}

@end
