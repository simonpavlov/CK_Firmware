#include "../storage.h"
#include <emul/emulator.h>

/*
 * http://stackoverflow.com/questions/2351087/what-is-the-best-32bit-hash-function-for-short-strings-tag-names
 */
uint32_t hash(const char *string)
{
    uint32_t h;
    const unsigned char *p;

    h = 0;
    for (p = string; *p != '\0'; ++p)
        h = 37 * h + *p;
    return h; // or, h % ARRAY_SIZE;
}

item_ptr
read_item(storage_item *item, uint32_t item_id)
{
    item_ptr item_ptr = STORAGE_START, i;
    char *item_p;
    do
    {
        // Read item from flash
        item_p = (char *) item;
        for (i = item_ptr; i < item_ptr + sizeof(storage_item); ++i)
            *item_p++ = storage_read_byte(i);
        // Check item id
        if (item->id == item_id) break;
        // Next item
        item_ptr = item->next;
    }
    while (item_ptr != NO_ITEM_FOUND);
    // Return pointer to item or NO_ITEM_FOUND
    return item_ptr;
}

item_ptr
write_item(storage_item *item)
{
    item_ptr item_ptr, i;
    storage_item tmp_item;
    // Start item element
    tmp_item.next = STORAGE_START;
    char *item_p;
    do
    {
        // Next item
        item_ptr = tmp_item.next;
        // Read item from flash
        item_p = (char *) &tmp_item;
        for (i = item_ptr; i < item_ptr + sizeof(storage_item); ++i)
            *item_p++ = storage_read_byte(i);
    }
    while (tmp_item.next != NO_ITEM_FOUND);
    // Update last item
    tmp_item.next = item_ptr + sizeof(storage_item) + tmp_item.size;
    item_p = (char *) &tmp_item;
    for (i = item_ptr; i < item_ptr + sizeof(storage_item); ++i)
        storage_write_byte(i, *item_p++);
    // Rift over last item
    item_ptr = tmp_item.next;
    // Write new item header
    item_p = (char *) item;
    for (i = item_ptr; i < item_ptr + sizeof(storage_item); ++i)
        storage_write_byte(i, *item_p++);
    // Return data start
    return item_ptr + sizeof(storage_item);
}


void
save_password(Password *msg)
{
    // Allocate item
    storage_item item;
    // Calculate hash of login and password
    item.id = hash(msg->login);
    // Set noitem next
    item.next = NO_ITEM_FOUND;
    // Set data size
    item.size = msg->size;
    // Write item to the end of DB
    item_ptr data_ptr = write_item(&item);

    // Store login
    const char *str_p = msg->login;
    while (*str_p)
        storage_write_byte(data_ptr++, *str_p++);
    storage_write_byte(data_ptr++, 0); // Zero end

    // Store password
    str_p = msg->password;
    while (*str_p)
        storage_write_byte(data_ptr++, *str_p++);
    storage_write_byte(data_ptr++, 0); // Zero end
}

Password *
load_password(const char *login)
{
    // Calculate item id
    uint32_t id = hash(login);
    storage_item item;

    item_ptr data = read_item(&item, id);
    if (data == NO_ITEM_FOUND)
        return 0;

    // Rift item header
    data += sizeof(storage_item);

    // Allocate space
    Password *msg = malloc(sizeof(Password));
    char *buffer     = malloc(item.size);
    char *buf_p      = buffer;

    // Set message size
    msg->size = item.size;

    buf_p = buffer;
    char strlen = 0;
    // Read login into memory
    do
    {
        *buf_p = storage_read_byte(data++);
        ++strlen;
    }
    while (*buf_p++);
    msg->login = malloc(strlen);         // Allocate string size
    memcpy(msg->login, buffer, strlen);  // Copy string

    buf_p = buffer;
    strlen = 0;
    // Read password into memory
    do
    {
        *buf_p = storage_read_byte(data++);
        ++strlen;
    }
    while (*buf_p++);
    msg->password = malloc(strlen);         // Allocate string size
    memcpy(msg->password, buffer, strlen);  // Copy string

    free(buffer); // Free buffer
    return msg;
}

void
storage_clean(void)
{
    storage_item tmp_item;
    // Start empty element
    tmp_item.next = NO_ITEM_FOUND;
    tmp_item.size = 0;
    // Dump item to flash
    char *item_p = (char *) &tmp_item,
          pos    = STORAGE_START;
    while(item_p < (char *) &tmp_item + sizeof(storage_item))
        storage_write_byte(pos++, *item_p++);
}
