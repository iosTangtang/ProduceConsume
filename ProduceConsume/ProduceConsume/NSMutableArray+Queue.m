//
//  NSMutableArray+Queue.m
//  ProducerConsumerOC
//
//  Created by Tangtang on 2016/10/13.
//  Copyright © 2016年 Tangtang. All rights reserved.
//

#import "NSMutableArray+Queue.h"

@implementation NSMutableArray (Queue)

#pragma mark - Queue Operation
- (void)pcr_enterQueue:(NSString *)str {
    
    [self addObject:str];
}

- (BOOL)pcr_delQueue {
    
    if (self.count == 0) {
        return  NO;
    }
    
    [self removeObjectAtIndex:0];
    
    return YES;
}

@end
