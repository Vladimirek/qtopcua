/****************************************************************************
**
** Copyright (C) 2017 basysKom GmbH, opensource@basyskom.com
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtOpcUa module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qopcuamonitoringparameters.h"
#include "private/qopcuamonitoringparameters_p.h"

QT_BEGIN_NAMESPACE

/*!
    \enum QOpcUaMonitoringParameters::MonitoringMode

    This enum is used to set the monitoring mode for a monitored item.

    \value Disabled Sampling is disabled and no notifications are being generated.
    \value Sampling Sampling is enabled and notifications are generated and queued, but reporting is disabled.
    \value Reporting Sampling is enabled, notifications are generated and queued, reporting is enabled.
*/

/*!
    \enum QOpcUaMonitoringParameters::SubscriptionType

    \value Shared Share subscription with other monitored items with the same interval
    \value Exclusive Request a new subscription for this attribute
*/

/*!
    \class QOpcUaMonitoringParameters

    This struct contains parameters for the creation of the subscription and monitored items for
    a enableMonitoring request.

    The same struct is used as return value for monitoringStatus and contains
    the revised values from the server.
*/

/*!
    \enum QOpcUaMonitoringParameters::Parameter

    Enumerates parameters that can be modified at runtime using \l modifyMonitoring().
    Not all values are guaranteed to be supported by all plugins. Lack of support will be reported
    in the \l monitoringStatusChanged signal.

    \value PublishingEnabled
    \value PublishingInterval
    \value LifetimeCount
    \value MaxKeepAliveCount
    \value MaxNotificationsPerPublish
    \value Priority
    \value SamplingInterval
    \value Filter
    \value QueueSize
    \value DiscardOldest
    \value MonitoringMode
*/

/*!
    \class QOpcUaMonitoringParameters::DataChangeFilter

    This struct is used to set up filtering for a DataChange monitored item.
    It is defined in OPC-UA part 4, 7.12.2.
*/

/*!
    \variable QOpcUaMonitoringParameters::DataChangeFilter::trigger

    The trigger for this filter.
*/

/*!
    \variable QOpcUaMonitoringParameters::DataChangeFilter::deadbandType

    The deadband type for this filter.
*/

/*!
    \variable QOpcUaMonitoringParameters::DataChangeFilter::deadbandValue

    The deadband value for this filter.
*/

/*!
    \enum QOpcUaMonitoringParameters::DataChangeFilter::DataChangeTrigger

    Enumerates the possible triggers for a \l DataChangeFilter.

    \value Status Triggers if the status code for the value changes.
    \value StatusValue Triggers if the status code or the value changes.
    \value StatusValueTimestamp Triggers if the status code, the value or the source timestamp changes.
*/

/*!
    \enum QOpcUaMonitoringParameters::DataChangeFilter::DeadbandType

    Enumerates the possible deadband types for a \l DataChangeFilter.

    \value None No deadband filtering.
    \value Absolute A notification is generated if the absolute value of the difference between the last cached value
           and the current value is greater than the deadband value.
    \value Percent Only valid for AnalogItems with an EURange property. A notification is generated if the absolute value
           of the difference between the last cached value and the current value is greater than value percent of the EURange.
*/

QOpcUaMonitoringParameters::QOpcUaMonitoringParameters()
    : d_ptr(new QOpcUaMonitoringParametersPrivate())
{}

QOpcUaMonitoringParameters::~QOpcUaMonitoringParameters()
{}

/*!
    This is the constructor which covers most use cases for the QtOpcUa user.
    \a publishingInterval must be supplied, \a shared and \a subscriptionId are optional.
*/
QOpcUaMonitoringParameters::QOpcUaMonitoringParameters(double publishingInterval, QOpcUaMonitoringParameters::SubscriptionType shared, quint32 subscriptionId)
    : d_ptr(new QOpcUaMonitoringParametersPrivate)
{
    d_ptr->publishingInterval = publishingInterval;
    d_ptr->shared = shared;
    d_ptr->subscriptionId = subscriptionId;

}

QOpcUaMonitoringParameters::QOpcUaMonitoringParameters(const QOpcUaMonitoringParameters &other)
    : d_ptr(other.d_ptr)
{}

QOpcUaMonitoringParameters &QOpcUaMonitoringParameters::operator=(const QOpcUaMonitoringParameters &other)
{
    d_ptr = other.d_ptr;
    return *this;
}

/*!
    Returns the subscription type.
*/
QOpcUaMonitoringParameters::SubscriptionType QOpcUaMonitoringParameters::shared() const
{
    return d_ptr->shared;
}

/*!
    Request \a shared as subscription type for the subscription.
*/
void QOpcUaMonitoringParameters::setShared(SubscriptionType shared)
{
    d_ptr->shared = shared;
}

/*!
    Returns the status code of the monitored item creation.
*/
QOpcUa::UaStatusCode QOpcUaMonitoringParameters::statusCode() const
{
    return d_ptr->statusCode;
}

/*!
    Set the status code to \a statusCode.
*/
void QOpcUaMonitoringParameters::setStatusCode(QOpcUa::UaStatusCode statusCode)
{
    d_ptr->statusCode = statusCode;
}

/*!
    Returns the publishing mode for the subscription.
*/
bool QOpcUaMonitoringParameters::publishingEnabled() const
{
    return d_ptr->publishingEnabled;
}

/*!
    Set \a publishingEnabled as publishing mode for the subscription.
*/
void QOpcUaMonitoringParameters::setPublishingEnabled(bool publishingEnabled)
{
    d_ptr->publishingEnabled = publishingEnabled;
}

/*!
    Returns the priority of the subscription used for the monitored item.
*/
quint8 QOpcUaMonitoringParameters::priority() const
{
    return d_ptr->priority;
}

/*!
    Set \a priority as priority for the subscription.
*/
void QOpcUaMonitoringParameters::setPriority(quint8 priority)
{
    d_ptr->priority = priority;
}

/*!
    Returns the maximum notifications per publish value of the subscription.
*/
quint32 QOpcUaMonitoringParameters::maxNotificationsPerPublish() const
{
    return d_ptr->maxNotificationsPerPublish;
}

/*!
    Request \a maxNotificationsPerPublish as maximum notifications per publish value for the subscription.
*/
void QOpcUaMonitoringParameters::setMaxNotificationsPerPublish(quint32 maxNotificationsPerPublish)
{
    d_ptr->maxNotificationsPerPublish = maxNotificationsPerPublish;
}

/*!
    Returns the maximum keepalive count of the subscription.
*/
quint32 QOpcUaMonitoringParameters::maxKeepAliveCount() const
{
    return d_ptr->maxKeepAliveCount;
}

/*!
    Request \a maxKeepAliveCount as maximum keepalive count for the subscription.
*/
void QOpcUaMonitoringParameters::setMaxKeepAliveCount(quint32 maxKeepAliveCount)
{
    d_ptr->maxKeepAliveCount = maxKeepAliveCount;
}

/*!
    Returns the lifetime count of the subscription.
*/
quint32 QOpcUaMonitoringParameters::lifetimeCount() const
{
    return d_ptr->lifetimeCount;
}

/*!
    Request \a lifetimeCount as lifetime count for the subscription.
*/
void QOpcUaMonitoringParameters::setLifetimeCount(quint32 lifetimeCount)
{
    d_ptr->lifetimeCount = lifetimeCount;
}

/*!
    Returns the publishing interval of the subscription.
*/
double QOpcUaMonitoringParameters::publishingInterval() const
{
    return d_ptr->publishingInterval;
}

/*!
    Request \a publishingInterval as publishing interval for the subscription.
*/
void QOpcUaMonitoringParameters::setPublishingInterval(double publishingInterval)
{
    d_ptr->publishingInterval = publishingInterval;
}

/*!
    Returns the assigned subscription id.
*/
quint32 QOpcUaMonitoringParameters::subscriptionId() const
{
    return d_ptr->subscriptionId;
}

/*!
    Request the monitored items to be created on a known subscription with subscriptionId \a value.
*/
void QOpcUaMonitoringParameters::setSubscriptionId(quint32 subscriptionId)
{
    d_ptr->subscriptionId = subscriptionId;
}

/*!
    Returns the monitoring mode for the monitored item.
*/
QOpcUaMonitoringParameters::MonitoringMode QOpcUaMonitoringParameters::monitoringMode() const
{
    return d_ptr->monitoringMode;
}

/*!
    Request \a monitoringMode as monitoring mode for the monitored item.
*/
void QOpcUaMonitoringParameters::setMonitoringMode(MonitoringMode monitoringMode)
{
    d_ptr->monitoringMode = monitoringMode;
}

/*!
    Returns the discardOldest setting of the monitored item.
*/
bool QOpcUaMonitoringParameters::discardOldest() const
{
    return d_ptr->discardOldest;
}

/*!
    Request \a discardOldest as discardOldest setting for the monitored item.
*/
void QOpcUaMonitoringParameters::setDiscardOldest(bool discardOldest)
{
    d_ptr->discardOldest = discardOldest;
}

/*!
    Returns the queue size of the monitored item.
*/
quint32 QOpcUaMonitoringParameters::queueSize() const
{
    return d_ptr->queueSize;
}

/*!
    Request \a queueSize as queue size for the monitored item.
*/
void QOpcUaMonitoringParameters::setQueueSize(quint32 queueSize)
{
    d_ptr->queueSize = queueSize;
}

/*!
    Returns the filter result. Empty for DataChangeFilter.
*/
QVariant QOpcUaMonitoringParameters::filter() const
{
    return d_ptr->filter;
}

/*!
    Request \a filter as filter for for the monitored item.
*/
void QOpcUaMonitoringParameters::setFilter(const QVariant &filter)
{
    d_ptr->filter = filter;
}

/*!
    Returns the revised sampling interval of the monitored item.
*/
double QOpcUaMonitoringParameters::samplingInterval() const
{
    return d_ptr->samplingInterval;
}

/*!
    Request \a samplingInterval as sampling interval for the monitored item.
*/
void QOpcUaMonitoringParameters::setSamplingInterval(double samplingInterval)
{
    d_ptr->samplingInterval = samplingInterval;
}

QT_END_NAMESPACE