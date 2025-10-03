// Connector.cpp : Implementation of CConnector

#include "pch.h"
#include "Connector.h"
#include <comdef.h>

// CConnector


std::string CConnector::conventer(const char* str)
{
	std::string res;
	int result_u, result_c;

	result_u = MultiByteToWideChar(CP_UTF8, 0, str, -1, 0, 0);

	if (!result_u)
		return 0;

	wchar_t* ures = new wchar_t[result_u];

	if (!MultiByteToWideChar(CP_UTF8, 0, str, -1, ures, result_u))
	{
		delete[] ures;
		return 0;
	}

	result_c = WideCharToMultiByte(1251, 0, ures, -1, 0, 0, 0, 0);

	if (!result_c)
	{
		delete[] ures;
		return 0;
	}

	char* cres = new char[result_c];

	if (!WideCharToMultiByte(1251, 0, ures, -1, cres, result_c, 0, 0))
	{
		delete[] cres;
		return 0;
	}
	delete[] ures;
	res.append(cres);
	delete[] cres;
	return res;
}
STDMETHODIMP CConnector::setPLUNumber(LONG number)
{
	plu.setNumber(number);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUName(BSTR name)
{
	std::string str = _bstr_t(name,false);
	plu.setName(str);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUItemCode(LONG itemCode)
{
	plu.setItemCode(itemCode);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUIndexBarcode(BSTR indexBarcode)
{

	std::string str = _bstr_t(indexBarcode, false);
	plu.setIndexBarcode(str);
	return S_OK;
}


STDMETHODIMP CConnector::setPLUAffileatedClass(LONG affileatedClass)
{
	plu.setAffileatedClass(affileatedClass);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUUnit(LONG unit)
{
	plu.setUnit(unit);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUTare(FLOAT tare)
{
	plu.setTare(tare);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUUnitPrice(FLOAT unitPrice)
{
	plu.setUnitPrice(unitPrice);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUCost(FLOAT cost)
{
	plu.setCost(cost);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUBarcodeId(LONG barcodeId)
{
	plu.setBardodeId(barcodeId);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUBarcodeFlag(LONG barcodeFlag)
{
	plu.setBarcodeFlag(barcodeFlag);

	return S_OK;
}

STDMETHODIMP CConnector::setPLUText1(BSTR text)
{
	std::string str = _bstr_t(text, false);
	plu.setText1(str);
	return S_OK;
}

STDMETHODIMP CConnector::setPLUText2(BSTR text2)
{
	std::string str = _bstr_t(text2, false);
	plu.setText2(str);
	return S_OK;
}

STDMETHODIMP CConnector::setPLUText3(BSTR text3)
{
	std::string str = _bstr_t(text3, false);
	plu.setText3(str);
	return S_OK;
}

STDMETHODIMP CConnector::setPLUText4(BSTR text4)
{
	std::string str = _bstr_t(text4, false);
	plu.setText4(str);
	return S_OK;
}

STDMETHODIMP CConnector::setPLUText5(BSTR text5)
{
	std::string str = _bstr_t(text5, false);
	plu.setText5(str);
	return S_OK;
}

STDMETHODIMP CConnector::setPLUText6(BSTR text6)
{
	std::string str = _bstr_t(text6, false);
	plu.setText6(str);
	return S_OK;
}

STDMETHODIMP CConnector::setPLUText7(BSTR text7)
{
	std::string str = _bstr_t(text7, false);
	plu.setText7(str); 
	return S_OK;
}



STDMETHODIMP CConnector::setPLUPrintSaleData(LONG printSaleData)
{
	plu.setPrintSaleData(printSaleData);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUPrintSaleTime(LONG printSaleTime)
{
	plu.setPrintSaleTime(printSaleTime);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUPrintPackTime(LONG printPackTime)
{
	plu.setPrintPackTime(printPackTime);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUPrintPackData(LONG printPackData)
{
	plu.setPrintPackDate(printPackData);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUPrintShelfData(LONG printShelfData)
{
	plu.setPrintShelfDate(printShelfData);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUSaleData(LONG saleData)
{
	plu.setSaleData(saleData);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUSaleTime(LONG saleTime)
{
	plu.setSaleTime(saleTime);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUPackTime(LONG packTime)
{
	plu.setPackTime(packTime);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUPackData(LONG packData)
{
	plu.setPackDate(packData);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUShelfData(FLOAT shelfData)
{
	plu.setShelfDate(shelfData);

	return S_OK;
}


STDMETHODIMP CConnector::setPLUCode(LONG PLUCode)
{
	pluKey.setPLUCode(PLUCode);

	return S_OK;
}


STDMETHODIMP CConnector::setKeyCode(LONG keyCode)
{
	pluKey.setKeyCode(keyCode);

	return S_OK;
}


STDMETHODIMP CConnector::setScalesPort(LONG port)
{
	client.setScalesPort(port);
	
	return S_OK;
}


STDMETHODIMP CConnector::setScalesIp(BSTR ip)
{
	std::string str = _bstr_t(ip, false);
	client.setScalesIp(str);

	return S_OK;
}


STDMETHODIMP CConnector::connectToScales()
{
	client.connectToScales();
	if (client.getException() != "")
	{
		return E_FAIL;
	}
	else
	{
		return S_OK;
	}
	return S_OK;
}


STDMETHODIMP CConnector::uploadPLUToScales()
{
	client.addPLUToScales(plu);

	return S_OK;
}


STDMETHODIMP CConnector::uploadPLUKeyBindingsToScales()
{
	client.bindPLUToKey(pluKey);

	return S_OK;
}

STDMETHODIMP CConnector::setPLUPrintFormat(LONG printFormat)
{
	plu.setPrintFormat(printFormat);

	return S_OK;
}


STDMETHODIMP CConnector::getException(BSTR* exception)
{
	*exception = SysAllocString(CA2W(client.getException().c_str()));

	return S_OK;
}


STDMETHODIMP CConnector::setSleep(LONG sleep)
{
	client.setSleep(sleep);

	return S_OK;
}


STDMETHODIMP CConnector::addPLUToQueue()
{
	plu.addPLUToQueue();
	return S_OK;
}


STDMETHODIMP CConnector::setTime(LONG year, LONG month, LONG day, LONG hour, LONG minute, LONG seconds)
{
	client.setTime(year, month, day, hour, minute, seconds);
	return S_OK;
}


STDMETHODIMP CConnector::clearPLU(LONG number)
{
	client.clearPLU(number);
	return S_OK;
}


STDMETHODIMP CConnector::getTime(BSTR* time)
{
	*time = SysAllocString(CA2W(conventer(client.getTime().c_str()).c_str()));
	return S_OK;
}


STDMETHODIMP CConnector::setKeyPage(LONG page)
{
	pluKey.setKeyPage(page);
	return S_OK;
}


STDMETHODIMP CConnector::addPLUKeyToQueue()
{
	pluKey.addPLUKeyToQueue();
	return S_OK;
}


STDMETHODIMP CConnector::getScalesAccaunt(LONG number, BSTR* accaunt)
{
	*accaunt = SysAllocString(CA2W(conventer(report.getReportText(client.getScalesAccaunt(number)).c_str()).c_str()));
	return S_OK;
}


STDMETHODIMP CConnector::getSummedScalesAccaunt(LONG number, BSTR* accaunt)
{
	*accaunt = SysAllocString(CA2W(conventer(report.getSummaryReport(client.getScalesAccaunt(number)).c_str()).c_str()));
	return S_OK;
}


STDMETHODIMP CConnector::getInfo(BSTR* info)
{
	*info = SysAllocString(CA2W(conventer(client.getInfo().c_str()).c_str()));
	return S_OK;
}


STDMETHODIMP CConnector::getMac(BSTR* mac)
{
	*mac = SysAllocString(CA2W(conventer(client.getMAC().c_str()).c_str()));
	return S_OK;
}


STDMETHODIMP CConnector::disconnect()
{
	client.disconnect();
	return S_OK;
}


STDMETHODIMP CConnector::readTMAFile(BSTR* file)
{
	client.readTMAFile((const std::string)_bstr_t(*file, false));
	return S_OK;
}
// Реалізація TMT методів
STDMETHODIMP CConnector::sendConstTMT(LONG fieldNumber, BSTR value, BSTR* result)
{
	if (result == nullptr) return E_POINTER;
	*result = nullptr;

	try {
		// 🔄 Коректна конвертація з BSTR (UTF-16) → CP1251 string
		int len = SysStringLen(value);
		if (len == 0) {
			client.sendConstTMT(fieldNumber, "");
			*result = SysAllocString(L"");
			return S_OK;
		}


		int size_needed = WideCharToMultiByte(1251, 0, value, len, NULL, 0, NULL, NULL);
		if (size_needed <= 0) return E_FAIL;

		std::string sValue(size_needed, '\0');
		WideCharToMultiByte(1251, 0, value, len, &sValue[0], size_needed, NULL, NULL);

		// Відправляємо через клієнт (який далі вже робить CP1251 → UTF8)
		std::string response = client.sendConstTMT(fieldNumber, sValue);

		// Повернення відповіді назад у BSTR (UTF-16)
		std::wstring wResponse(response.begin(), response.end()); // припускаємо що response — ASCII
		*result = SysAllocString(wResponse.c_str());
		return S_OK;
	}
	catch (...) {
		return E_FAIL;
	}
}


STDMETHODIMP CConnector::uploadTMTToScales()
{

	try {
		// Відправляємо всі збережені значення
		if (!m_shopName.empty()) {
			client.sendConstTMT(0, m_shopName);
			Sleep(100);
		}

		if (!m_deviceName.empty()) {
			client.sendConstTMT(1, m_deviceName);
			Sleep(100);
		}

		if (!m_currency.empty()) {
			client.sendConstTMT(2, m_currency);
			Sleep(100);
		}
		if (!m_currency.empty()) {
			client.sendConstTMT(3, m_currency);
			Sleep(100);
		}
		if (!m_currency.empty()) {
			client.sendConstTMT(4, m_currency);
			Sleep(100);
		}
		if (!m_currency.empty()) {
			client.sendConstTMT(5, m_currency);
			Sleep(100);
		}
		if (!m_currency.empty()) {
			client.sendConstTMT(6, m_currency);
			Sleep(100);
		}
		if (!m_currency.empty()) {
			client.sendConstTMT(7, m_currency);
			Sleep(100);
		}

		// ... аналогічно для інших полів ...

		return S_OK;
	}
	catch (...) {
		return E_FAIL;
	}
}
