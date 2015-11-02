//
//  RoundedButton.m
//  DemoApp
//
//  Created by Michael Spensieri on 2/28/14.
//  Copyright (c) 2015 Smooch Technologies. All rights reserved.
//

#import "RoundedButton.h"

static const int buttonSidePadding = 30;

@implementation RoundedButton

-(id)initWithFrame:(CGRect)frame
{
    return [self initWithFrame:frame cornerRadius:23.0];
}

-(id)initWithFrame:(CGRect)frame cornerRadius:(CGFloat)radius
{
    self = [super initWithFrame:frame];
    if(self){
        self.layer.cornerRadius = radius;
        self.layer.masksToBounds = YES;
        self.backgroundColor = [UIColor clearColor];
        [self setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [self setTitleColor:[UIColor colorWithRed:136/255.0 green:136/255.0 blue:136/255.0 alpha:1] forState:UIControlStateHighlighted];
        self.titleLabel.font = [UIFont systemFontOfSize:20];
        
        if(floor(NSFoundationVersionNumber) <= NSFoundationVersionNumber_iOS_6_1){
            [self setTitleColor:[[UIColor whiteColor] colorWithAlphaComponent:0.2] forState:UIControlStateHighlighted];
            [self setBackgroundImage:[UIImage new] forState:UIControlStateNormal];
        }
        
        self.layer.borderColor = [UIColor whiteColor].CGColor;
        self.layer.borderWidth = 1.0f;
    }
    return self;
}

- (CGSize)sizeThatFits:(CGSize)size{
    CGSize newSize = [super sizeThatFits:size];
    newSize.width = newSize.width + buttonSidePadding;
    newSize.height = size.height;
    return newSize;
}

@end
