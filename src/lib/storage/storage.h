#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include <IO/message.h>

#define NO_ITEM_FOUND 0xFFFF
#define STORAGE_START 0

// Typedef item pointer
typedef uint16_t item_ptr;

/*
 * Storage item
 * TODO: item type
 */
typedef struct {
    uint32_t    id;     // Is a hash from login and password concatenation
    item_ptr    next;   // Next item start in bytes
    uint32_t    size;   // Item data size
} storage_item;

/*
 * Simple hash function.
 * @param hashed string zero ended
 */
uint32_t hash(const char *);

/*
 * Item reader function.
 * @param storage item struct pointer
 * @param item id
 * @returns item data pointer.
 *
 * Read item by id.
 */
item_ptr
read_item(storage_item *, uint32_t);

/*
 * Item saver function.
 * @param item
 * @returns item data pointer.
 *
 * Write item to the end of DB.
 */
item_ptr
write_item(storage_item *);

/*
 * Password saver.
 * @param password structure
 */
void
save_password(Password *);

/*
 * Password loader.
 * @param login string
 */
Password *
load_password(const char *);

/*
 * Storage initialisation.
 */
void
storage_clean();

#endif // STORAGE_MANAGER_H
