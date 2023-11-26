#include "phone.h"

#include <QProcess>

PhoneDaemon::PhoneDaemon(QObject *parent) 
	: QObject(parent)
	, m_modemSettings(ModemSettings(this)) {
	QList<CutieModem*> modemList = m_modemSettings.modems();
	m_modems = QSet(modemList.begin(), modemList.end());
	for (CutieModem *m : m_modems) {
		connect(m, &CutieModem::callsChanged, this, &PhoneDaemon::onCallsChanged);
	}

	connect(&m_modemSettings, &ModemSettings::modemsChanged, this, &PhoneDaemon::onModemsChanged);
}

void PhoneDaemon::onCallsChanged(QList<CutieCall*> calls) {
	if (calls.length() > 0)
    	if (!QProcess::startDetached("/usr/bin/cutie-ongoing-call", QStringList()))
        	qDebug() << "Failed to run";
}

void PhoneDaemon::onModemsChanged(QList<CutieModem*> modems) {
	QSet<CutieModem*> modemSet(modems.begin(), modems.end());

	for (CutieModem* added : modemSet - m_modems) {
		connect(added, &CutieModem::callsChanged, this, &PhoneDaemon::onCallsChanged);
		m_modems.insert(added);
	}

	for (CutieModem* removed : m_modems - modemSet) {
		disconnect(removed, &CutieModem::callsChanged, 0, 0);
		m_modems.remove(removed);
	}
}