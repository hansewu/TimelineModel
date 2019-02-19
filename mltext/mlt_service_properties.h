

#ifndef __MLT_SERVICE_PROPERTIES_H__
#define __MLT_SERVICE_PROPERTIES_H__


mlt_mix

QUuid Controller::uuid(Mlt::Properties &properties) const
{
    return QUuid(properties.get(kUuidProperty));
}

#endif // __MLT_SERVICE_PROPERTIES_H__
