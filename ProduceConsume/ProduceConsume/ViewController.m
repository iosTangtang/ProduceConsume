//
//  ViewController.m
//  ProduceConsume
//
//  Created by Tangtang on 2016/10/14.
//  Copyright © 2016年 Tangtang. All rights reserved.
//

#import "ViewController.h"
#import "ProducerConsumer.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    ProducerConsumer *pro = [[ProducerConsumer alloc] init];
    
    [pro start];
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
