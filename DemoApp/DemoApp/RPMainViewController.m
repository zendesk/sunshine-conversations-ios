//
//  RPSideMenuViewController.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/10/13.
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import "RPMainViewController.h"
#import "RPMainContentView.h"
#import "RPZendeskPickerView.h"
#import <SupportKit/SupportKit.h>

@interface RPMainViewController ()

@property NSString* initialURL;
@property RPMainContentView* contentView;
@property RPZendeskPickerView* pickerView;
@property BOOL showingSidePanel;

@end

@implementation RPMainViewController

+ (UIImage *)menuImage {
	static UIImage *defaultImage = nil;
	static dispatch_once_t onceToken;
	dispatch_once(&onceToken, ^{
		UIGraphicsBeginImageContextWithOptions(CGSizeMake(20.f, 13.f), NO, 0.0f);
		
		[[UIColor blackColor] setFill];
		[[UIBezierPath bezierPathWithRect:CGRectMake(0, 0, 20, 1)] fill];
		[[UIBezierPath bezierPathWithRect:CGRectMake(0, 5, 20, 1)] fill];
		[[UIBezierPath bezierPathWithRect:CGRectMake(0, 10, 20, 1)] fill];
		
		[[UIColor whiteColor] setFill];
		[[UIBezierPath bezierPathWithRect:CGRectMake(0, 1, 20, 2)] fill];
		[[UIBezierPath bezierPathWithRect:CGRectMake(0, 6,  20, 2)] fill];
		[[UIBezierPath bezierPathWithRect:CGRectMake(0, 11, 20, 2)] fill];
		
		defaultImage = UIGraphicsGetImageFromCurrentImageContext();
		UIGraphicsEndImageContext();
        
	});
    return defaultImage;
}

-(id)initWithZendeskURL:(NSString*)zendeskURL
{
    self = [super init];
    if(self){
        self.initialURL = zendeskURL;
    }
    return self;
}

-(void)viewDidLoad
{
    [super viewDidLoad];
    
    self.showingSidePanel = NO;
    self.view.backgroundColor = [UIColor whiteColor];
    
    [self initContentView];
    [self initPickerView];
}

-(void)initContentView
{
    self.contentView = [[RPMainContentView alloc] initWithFrame:[self getContentViewFrame]];
    
    UINavigationItem* navItem = [[UINavigationItem alloc] initWithTitle:@"We ❤️ Radialpoint"];
    navItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[self.class menuImage] style:UIBarButtonItemStylePlain target:self action:@selector(showMenu)];
    navItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Help" style:UIBarButtonItemStylePlain target:self action:@selector(launch)];
    [self.contentView.navBar pushNavigationItem:navItem animated:NO];
    
    [self.contentView.button addTarget:self action:@selector(launch) forControlEvents:UIControlEventTouchUpInside];
    [self.contentView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(hideMenu)]];
    
    [self.view addSubview:self.contentView];
}

-(void)initPickerView
{
    self.pickerView = [[RPZendeskPickerView alloc] initWithFrame:[self getPickerViewFrame]];
    self.pickerView.hidden = YES;
    self.pickerView.textField.text = self.initialURL;
    self.pickerView.backgroundColor = [UIColor colorWithRed:0.8 green:0.8 blue:0.8 alpha:1];
    
    [self.view addSubview:self.pickerView];
    
    [self.pickerView.button addTarget:self action:@selector(launch) forControlEvents:UIControlEventTouchUpInside];
    [self.pickerView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(dismissKeyboard)]];
}

-(void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    
    self.contentView.frame = [self getContentViewFrame];
    self.pickerView.frame = [self getPickerViewFrame];
}

-(void)launch
{
    if([self.pickerView.textField.text isEqualToString:@"https://supportkit.zendesk.com"]){
        [SupportKit showInViewController:self withZendeskURL:self.pickerView.textField.text andTicketURL:@"https://supportkit.zendesk.com/hc/en-us/requests/new"];
    }else{
        [SupportKit showInViewController:self withZendeskURL:self.pickerView.textField.text];
    }
}

-(void)showMenu
{
    self.showingSidePanel = YES;
    self.pickerView.hidden = NO;
    
    [UIView animateWithDuration:0.25 animations:^{
        self.contentView.frame = [self getContentViewFrame];
        self.pickerView.frame = [self getPickerViewFrame];
    }];
}

-(void)hideMenu
{
    self.showingSidePanel = NO;
    [self dismissKeyboard];
    
    [UIView animateWithDuration:0.25 animations:^{
        self.contentView.frame = [self getContentViewFrame];
        self.pickerView.frame = [self getPickerViewFrame];
    } completion:^(BOOL finished) {
        self.pickerView.hidden = YES;
    }];
}

-(CGRect)getPickerViewFrame
{
    CGRect frame = CGRectMake(0, 0, self.view.bounds.size.width * 0.7, self.view.bounds.size.height);
    if(!self.showingSidePanel){
        frame = CGRectOffset(frame, -self.view.bounds.size.width * 0.7, 0);
    }
    return frame;
}

-(CGRect)getContentViewFrame
{
    CGRect frame = self.view.bounds;
    if(self.showingSidePanel){
        frame = CGRectOffset(frame, self.view.bounds.size.width * 0.7, 0);
    }
    return frame;
}

#pragma mark - Shake Gesture

-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    // Enable the shake gesture
    [self becomeFirstResponder];
}

-(BOOL)canBecomeFirstResponder
{
    return YES;
}

-(void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
    if(event.type == UIEventSubtypeMotionShake){
        [self launch];
    }
}

-(void)dismissKeyboard
{
    // Hide the keyboard
    [self.pickerView.textField resignFirstResponder];
    
    // Re-enable the shake gesture
    [self becomeFirstResponder];
}


@end
