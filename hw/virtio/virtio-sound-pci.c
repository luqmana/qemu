/*
 * Virtio Sound PCI Bindings
 *
 */

#include "qemu/osdep.h"

#include "hw/virtio/virtio-sound.h"
#include "virtio-pci.h"

typedef struct VirtIOSoundPCI VirtIOSoundPCI;

/*
 * virtio-sound-pci: This extends VirtioPCIProxy.
 */
#define TYPE_VIRTIO_SOUND_PCI "virtio-sound-pci"
DECLARE_INSTANCE_CHECKER(VirtIOSoundPCI, VIRTIO_SOUND_PCI,
                         TYPE_VIRTIO_SOUND_PCI)

struct VirtIOSoundPCI {
    VirtIOPCIProxy parent_obj;
    VirtIOSound vdev;
};


static void virtio_sound_pci_instance_init(Object *obj)
{
    VirtIOSoundPCI *dev = VIRTIO_SOUND_PCI(obj);

    virtio_instance_init_common(obj, &dev->vdev, sizeof(dev->vdev),
                                TYPE_VIRTIO_SOUND);
}

static void virtio_sound_pci_realize(VirtIOPCIProxy *vpci_dev, Error **errp)
{
    VirtIOSoundPCI *vsound = VIRTIO_SOUND_PCI(vpci_dev);
    DeviceState *vdev = DEVICE(&vsound->vdev);

    qdev_realize(vdev, BUS(&vpci_dev->bus), errp);
}

static void virtio_sound_pci_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    VirtioPCIClass *k = VIRTIO_PCI_CLASS(klass);
    PCIDeviceClass *pcidev_k = PCI_DEVICE_CLASS(klass);

    k->realize = virtio_sound_pci_realize;
    set_bit(DEVICE_CATEGORY_SOUND, dc->categories);

    pcidev_k->vendor_id = PCI_VENDOR_ID_REDHAT_QUMRANET;
    pcidev_k->device_id = PCI_DEVICE_ID_VIRTIO_SOUND;
    pcidev_k->revision = VIRTIO_PCI_ABI_VERSION;
    pcidev_k->class_id = PCI_CLASS_MULTIMEDIA_AUDIO;
}

static const VirtioPCIDeviceTypeInfo virtio_sound_pci_info = {
    .generic_name   = TYPE_VIRTIO_SOUND_PCI,
    .instance_size  = sizeof(VirtIOSoundPCI),
    .instance_init  = virtio_sound_pci_instance_init,
    .class_init     = virtio_sound_pci_class_init,

};

static void virtio_sound_pci_register_types(void)
{
    virtio_pci_types_register(&virtio_sound_pci_info);
}

type_init(virtio_sound_pci_register_types)
