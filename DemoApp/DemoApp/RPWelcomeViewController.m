//
//  RPWelcomeViewController.m
//  DemoApp
//
//  Created by Michael Spensieri on 12/19/13.
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import "RPWelcomeViewController.h"
#import "RPZendeskPickerView.h"
#import "RPMainViewController.h"

@interface RPWelcomeViewController ()

@property RPZendeskPickerView* pickerView;

@end

@implementation RPWelcomeViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.pickerView = [[RPZendeskPickerView alloc] init];
    
    [self.pickerView.button addTarget:self action:@selector(tryIt) forControlEvents:UIControlEventTouchUpInside];
    
    [self.view addSubview:self.pickerView];
}

-(void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    
    self.pickerView.frame = self.view.bounds;
}

-(void)tryIt
{
    RPMainViewController* controller = [[RPMainViewController alloc] initWithZendeskURL:self.pickerView.textField.text];
    controller.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    
    [self presentViewController:controller animated:YES completion:nil];
}


@end
