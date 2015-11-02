//
//  MainContentView.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/19/13.
//  Copyright (c) 2015 Smooch Technologies. All rights reserved.
//

#import "MainContentView.h"
#import "RoundedButton.h"

static const int kLogoBottomPadding = 30;

@interface MainContentView()

@property UILabel* titleLabel;
@property UILabel* subtitleLabel;
@property CAGradientLayer* background;
@property UIImageView* logo;

@end

@implementation MainContentView

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
    [self initNavBar];
    [self initBackgroundColor];
    [self initLogo];
    [self initTitleLabel];
    [self initSubtitleLabel];
    [self initButton];
    [self initShadow];
}

-(void)initNavBar
{
    self.navBar = [[UINavigationBar alloc] init];
    
    if([self isIOS7OrLater]){
        self.navBar.tintColor = [UIColor colorWithRed:145.0/255 green:45.0/255 blue:141.0/255 alpha:1.0];
    }
    
    [self addSubview:self.navBar];
}

-(void)initBackgroundColor
{
    if (self.background) return;
    self.background = [CAGradientLayer layer];
    UIColor *purple = [UIColor colorWithRed:215.0/255 green:171.0/255 blue:207.0/255 alpha:1.0];
    UIColor *pink = [UIColor colorWithRed:248.0/255 green:179.0/255 blue:174.0/255 alpha:1.0];
    self.background.colors = [NSArray arrayWithObjects:(id)purple.CGColor, (id)pink.CGColor, nil];
    self.background.startPoint = CGPointMake(0, 0.5);
    self.background.endPoint = CGPointMake(1, 0.5);
    self.background.frame = self.bounds;
    [self.layer insertSublayer:self.background atIndex:0];
}

-(void)initLogo
{
    self.logo = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"logo"]];
    [self addSubview:self.logo];
}

-(void)initTitleLabel
{
    self.titleLabel = [[UILabel alloc] init];
    self.titleLabel.textColor = [self textColor];
    self.titleLabel.text = @"Welcome to Smooch";
    self.titleLabel.textAlignment = NSTextAlignmentCenter;
    self.titleLabel.font = [UIFont boldSystemFontOfSize:22];
    self.titleLabel.backgroundColor = [UIColor clearColor];
    
    [self addSubview:self.titleLabel];
}

-(void)initSubtitleLabel
{
    self.subtitleLabel = [[UILabel alloc] init];
    self.subtitleLabel.textColor = [self textColor];
    self.subtitleLabel.text = @"Smooch lets you build rich messaging inside your apps and websites. Try out this demo app to see what it can do for you.";
    self.subtitleLabel.textAlignment = NSTextAlignmentCenter;
    self.subtitleLabel.font = [UIFont systemFontOfSize:15];
    self.subtitleLabel.numberOfLines = 0;
    self.subtitleLabel.backgroundColor = [UIColor clearColor];
    
    [self addSubview:self.subtitleLabel];
}

-(void)initButton
{
    self.button = [RoundedButton new];
    [self.button setTitle:@"Smooch Me" forState:UIControlStateNormal];
    // Make the button purple
    self.button.backgroundColor = [self buttonColor];
    self.button.layer.borderColor = [self buttonColor].CGColor;
    [self.button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [self.button setTitleColor:[UIColor colorWithWhite:1.0 alpha:0.5] forState:UIControlStateHighlighted];
    [self addSubview:self.button];
}

-(void)initShadow
{
    self.layer.masksToBounds = NO;
    self.layer.shadowColor = [UIColor blackColor].CGColor;
    self.layer.shadowOffset = CGSizeMake(-2.0f, 0.0f);
    self.layer.shadowOpacity = 0.3f;
    self.layer.shadowRadius = 10.0f;
    self.layer.shadowPath = [UIBezierPath bezierPathWithRect:self.bounds].CGPath;
}

-(void)layoutSubviews
{
    [super layoutSubviews];
    
    CGFloat navBarHeight = [self getNavBarHeight];
    self.navBar.frame = CGRectMake(0, 0, self.bounds.size.width, navBarHeight);
    
    // Resize the gradient to fit the screensize when switching between landscape/portrait
    self.background.frame = self.frame;
    
    self.subtitleLabel.frame = CGRectMake(0, 0, MIN(self.bounds.size.width - 50, 320), 500);
    [self.subtitleLabel sizeToFit];
    self.subtitleLabel.center = CGPointMake(floor(CGRectGetMidX(self.bounds)), self.center.y + 20);
    
    [self.titleLabel sizeToFit];
    self.titleLabel.center = CGPointMake(self.subtitleLabel.center.x, self.subtitleLabel.frame.origin.y - 5 - floor(self.titleLabel.frame.size.height / 2));
    
    // Switch to a smaller logo when the phone is in landscape mode
    if ([self isLayoutPhoneInLandscape]) {
        self.logo.frame = CGRectMake(0, self.titleLabel.frame.origin.y - self.logo.frame.size.height/2 - kLogoBottomPadding, self.logo.image.size.width/2, self.logo.image.size.height/2);
    } else {
        self.logo.frame = CGRectMake(0, self.titleLabel.frame.origin.y - self.logo.frame.size.height - kLogoBottomPadding, self.logo.image.size.width, self.logo.image.size.height);
    }
    self.logo.center = CGPointMake(self.titleLabel.center.x, self.logo.center.y);
    
    self.button.frame = CGRectMake(0,CGRectGetMaxY(self.subtitleLabel.frame) + 10, 200, 46);
    self.button.center = CGPointMake(floor(CGRectGetMidX(self.bounds)), self.button.center.y);
}

-(CGFloat)getNavBarHeight
{
    int height = 44;
    
    if([self isLayoutPhoneInLandscape]){
        height = 32;
    }
    
    if([self isIOS7OrLater]){
        height += 20;
    }
    
    return height;
}

-(BOOL)isIOS7OrLater
{
    return floor(NSFoundationVersionNumber) > NSFoundationVersionNumber_iOS_6_1;
}

-(BOOL)isLayoutPhoneInLandscape
{
    return UIDeviceOrientationIsLandscape([UIDevice currentDevice].orientation) && UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone;
}

-(UIColor*)textColor {
    return [UIColor colorWithRed:38.0/255 green:38.0/255 blue:38.0/255 alpha:1.0];
}

-(UIColor*)buttonColor {
    return [UIColor colorWithRed:145.0/255 green:45.0/255 blue:141.0/255 alpha:1.0];
}

@end
