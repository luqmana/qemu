/*
 * Virtio Sound Device
 *
 */

#ifndef QEMU_VIRTIO_SOUND_H
#define QEMU_VIRTIO_SOUND_H

#include "audio/audio.h"
#include "hw/virtio/virtio.h"
#include "qom/object.h"

#define TYPE_VIRTIO_SOUND "virtio-sound-device"
OBJECT_DECLARE_SIMPLE_TYPE(VirtIOSound, VIRTIO_SOUND)
#define VIRTIO_SOUND_GET_PARENT_CLASS(obj) \
        OBJECT_GET_PARENT_CLASS(obj, TYPE_VIRTIO_SOUND)

struct VirtIOSound {
    VirtIODevice parent_obj;

    QEMUSoundCard card;

    VirtQueue *controlq;
    VirtQueue *eventq;
    VirtQueue *txq;
    VirtQueue *rxq;
};

#endif
