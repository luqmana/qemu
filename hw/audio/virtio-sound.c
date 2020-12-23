/*
 * Virtio Sound Device
 *
 */

#include "qemu/osdep.h"
#include "hw/virtio/virtio-sound.h"
#include "standard-headers/linux/virtio_ids.h"


static void virtio_sound_device_realize(DeviceState *dev, Error **errp)
{
    VirtIODevice *vdev = VIRTIO_DEVICE(dev);
    VirtIOSound *vsound = VIRTIO_SOUND(dev);

    AUD_register_card("virtio-sound", &vsound->card);

    virtio_init(vdev, "virtio-sound", VIRTIO_ID_SOUND, 0);
}

static void virtio_sound_device_unrealize(DeviceState *dev)
{
    VirtIOSound *vsound = VIRTIO_SOUND(dev);

    AUD_remove_card(&vsound->card);
}

static uint64_t virtio_sound_get_features(VirtIODevice *vdev, uint64_t features,
                                          Error **errp)
{
    (void)vdev; (void)errp;
    return features;
}

static uint64_t virtio_sound_bad_features(VirtIODevice *vdev)
{
    (void)vdev;
    uint64_t features = 0;
    return features;
}

static void virtio_sound_set_features(VirtIODevice *vdev, uint64_t features)
{
    (void)vdev; (void)features;
}

static int virtio_sound_validate_features(VirtIODevice *vdev)
{
    (void)vdev;
    return 0;
}

static void virtio_sound_get_config(VirtIODevice *vdev, uint8_t *config)
{
    (void)vdev; (void)config;
}

static void virtio_sound_set_config(VirtIODevice *vdev, const uint8_t *config)
{
    (void)vdev; (void)config;
}

static void virtio_sound_reset(VirtIODevice *vdev)
{
    (void)vdev;
}

static void virtio_sound_set_status(struct VirtIODevice *vdev, uint8_t status)
{
    (void)vdev; (void)status;
}

static Property virtio_sound_properties[] = {
    DEFINE_AUDIO_PROPERTIES(VirtIOSound, card),
    DEFINE_PROP_END_OF_LIST(),
};

static void virtio_sound_class_init(ObjectClass *klass, void *data)
{
    VirtioDeviceClass *vdc = VIRTIO_DEVICE_CLASS(klass);
    DeviceClass *dc = DEVICE_CLASS(klass);

    set_bit(DEVICE_CATEGORY_SOUND, dc->categories);

    vdc->realize = virtio_sound_device_realize;
    vdc->unrealize = virtio_sound_device_unrealize;
    vdc->get_features = virtio_sound_get_features;
    vdc->bad_features = virtio_sound_bad_features;
    vdc->set_features = virtio_sound_set_features;
    vdc->validate_features = virtio_sound_validate_features;
    vdc->get_config = virtio_sound_get_config;
    vdc->set_config = virtio_sound_set_config;
    vdc->reset = virtio_sound_reset;
    vdc->set_status = virtio_sound_set_status;

    device_class_set_props(dc, virtio_sound_properties);
}

static const TypeInfo virtio_sound_info = {
    .name = TYPE_VIRTIO_SOUND,
    .parent = TYPE_VIRTIO_DEVICE,
    .instance_size = sizeof(VirtIOSound),
    .class_init = virtio_sound_class_init,
};

static void virtio_register_types(void)
{
    type_register_static(&virtio_sound_info);
}

type_init(virtio_register_types)
