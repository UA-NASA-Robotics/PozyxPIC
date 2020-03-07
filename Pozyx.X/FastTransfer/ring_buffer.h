/* 
 * File:   ring_buffer.h
 * Author: Alex
 *
 * Created on February 8, 2020, 6:03 PM
 */

#ifndef RING_BUFFER_H
#define	RING_BUFFER_H

#define FT_DEFS


#ifdef FT_DEFS
#include "ft_config.h"
#endif

#include <stdint.h>
#include <stdbool.h>

#ifdef FT_DEFS
#define BUFFER_SIZE MAX_PCKT_SZ
#endif
#ifndef FT_DEFS
#define BUFFER_SIZE 200
#endif


#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct ring_buffer_t
    {
        uint8_t data[BUFFER_SIZE];
        uint64_t size;
        uint64_t head;
        uint64_t tail;
    }ring_buffer_t;
    
   
    
    void rbuffer_init(ring_buffer_t*);
    //struct ring_buffer_t rbuffer_t(void);
    uint64_t rbuffer_size(ring_buffer_t*);
    uint64_t rbuffer_increment(const uint64_t, const uint64_t);
    uint8_t rbuffer_pop(ring_buffer_t*);
    uint8_t rbuffer_peek(ring_buffer_t*);
    uint8_t rbuffer_get( ring_buffer_t*, uint32_t);
    void rbuffer_push( ring_buffer_t*, uint8_t data);
    void rbuffer_push2( ring_buffer_t*, uint8_t, uint8_t);
    void rbuffer_push3( ring_buffer_t*, uint8_t, uint8_t, uint8_t);
    void rbuffer_clear( ring_buffer_t*);
    void rbuffer_flush( ring_buffer_t*, uint8_t val);
    uint8_t* rbuffer_getarray( ring_buffer_t*);
    bool rbuffer_empty( ring_buffer_t*);
    bool rbuffer_full( ring_buffer_t*);
    void rbuffer_reset( ring_buffer_t*);

#ifdef	__cplusplus
}
#endif

#endif	/* RING_BUFFER_H */

