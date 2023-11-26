#pragma once

#include <cutiemodem.h>

class PhoneDaemon : public QObject {
	Q_OBJECT
public:
	PhoneDaemon(QObject *parent = nullptr);
public slots:
	void onCallsChanged(QList<CutieCall*> calls);
	void onModemsChanged(QList<CutieModem*> modems);
private:
	ModemSettings m_modemSettings;
	QSet<CutieModem*> m_modems;
};