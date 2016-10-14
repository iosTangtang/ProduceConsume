//
//  ProducerConsumer.m
//  ProduceConsume
//
//  Created by Tangtang on 2016/10/14.
//  Copyright © 2016年 Tangtang. All rights reserved.
//

#import "ProducerConsumer.h"
#import "NSMutableArray+Queue.h"

#define MAXSIZE 10

@interface ProducerConsumer () {
    NSMutableArray *_dataQueue;
    NSCondition *_condition;
}

@end

@implementation ProducerConsumer

- (instancetype)init
{
    self = [super init];
    if (self) {
        _dataQueue = [NSMutableArray array];
        _condition = [[NSCondition alloc] init];
    }
    return self;
}

#pragma mark - Produce and Consume
- (void)produce {
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    
    dispatch_async(queue, ^{
        while (1) {
            [_condition lock];
            if (_dataQueue.count > 10) {
                NSLog(@"a lot of item");
                
                [_condition wait];
            }
            [_dataQueue pcr_enterQueue:@"data"];
            NSLog(@" produce item  ");
            
            //唤醒其他线程
            [_condition broadcast];
            
            [_condition unlock];
        }
    });
}

- (void)consume {
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    
    dispatch_async(queue, ^{
        while (1) {
            [_condition lock];
            if (_dataQueue.count == 0) {
                NSLog(@"wait for item");
                
                [_condition wait];
            }
            [_dataQueue pcr_delQueue];
            NSLog(@" consume item ");
            
            //唤醒其他线程
            [_condition broadcast];
            
            [_condition unlock];
        }
    });
}

- (void)start {
//    NSThread *thread1 = [[NSThread alloc] initWithTarget:self selector:@selector(consume) object:nil];
//    
//    NSThread *thread2 = [[NSThread alloc] initWithTarget:self selector:@selector(produce) object:nil];
//    
//    [thread1 start];
//    [thread2 start];
    
    [self consume];
    
    [self produce];
}


@end
