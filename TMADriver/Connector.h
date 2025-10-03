// Connector.h : Declaration of the CConnector

#pragma once
#include "resource.h"       // main symbols



#include "TMADriver_i.h"
#include "PLU.h"
#include "PLUKey.h"
#include "Report.h"
#include "TMAClient.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CConnector

class ATL_NO_VTABLE CConnector :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CConnector, &CLSID_Connector>,
	public IDispatchImpl<IConnector, &IID_IConnector, &LIBID_TMADriverLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CConnector()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CConnector)
	COM_INTERFACE_ENTRY(IConnector)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(setPLUNumber)(LONG number);
	STDMETHOD(setPLUName)(BSTR name);
	STDMETHOD(setPLUItemCode)(LONG itemCode);
	STDMETHOD(setPLUIndexBarcode)(BSTR indexBarcode);
	STDMETHOD(setPLUAffileatedClass)(LONG affileatedClass);
	STDMETHOD(setPLUUnit)(LONG unit);
	STDMETHOD(setPLUTare)(FLOAT tare);
	STDMETHOD(setPLUUnitPrice)(FLOAT unitPrice);
	STDMETHOD(setPLUCost)(FLOAT cost);
	STDMETHOD(setPLUBarcodeId)(LONG barcodeId);
	STDMETHOD(setPLUBarcodeFlag)(LONG barcodeFlag);
	STDMETHOD(setPLUText1)(BSTR text1);
	STDMETHOD(setPLUText2)(BSTR text2);
	STDMETHOD(setPLUText3)(BSTR text3);
	STDMETHOD(setPLUText4)(BSTR text4);
	STDMETHOD(setPLUText5)(BSTR text5);
	STDMETHOD(setPLUText6)(BSTR text6);
	STDMETHOD(setPLUText7)(BSTR text7);
	STDMETHOD(setPLUPrintSaleData)(LONG printSaleData);
	STDMETHOD(setPLUPrintSaleTime)(LONG printSaleTime);
	STDMETHOD(setPLUPrintPackTime)(LONG printPackTime);
	STDMETHOD(setPLUPrintPackData)(LONG printPackData);
	STDMETHOD(setPLUPrintShelfData)(LONG printShelfData);
	STDMETHOD(setPLUSaleData)(LONG saleData);
	STDMETHOD(setPLUSaleTime)(LONG saleTime);
	STDMETHOD(setPLUPackTime)(LONG packTime);
	STDMETHOD(setPLUPackData)(LONG packData);
	STDMETHOD(setPLUShelfData)(FLOAT shelfData);
	private:
		PLU plu;
		PLUKey pluKey;
		Report report;
		TMAClient client;
		std::string CConnector::conventer(const char* str);
		std::string m_shopName;    // Для поля 0
		std::string m_deviceName;  // Для поля 1
		std::string m_currency;    // Для поля 2
		std::string ConvertBSTRToString(BSTR bstr)
		{
			if (!bstr) return "";
			std::wstring wstr(bstr, SysStringLen(bstr));
			return std::string(wstr.begin(), wstr.end());
		}
public:
	STDMETHOD(setPLUCode)(LONG PLUCode);
	STDMETHOD(setKeyCode)(LONG keyCode);
	STDMETHOD(setScalesPort)(LONG port);
	STDMETHOD(setScalesIp)(BSTR ip);
	STDMETHOD(connectToScales)();
	STDMETHOD(uploadPLUToScales)();
	STDMETHOD(uploadPLUKeyBindingsToScales)();
	STDMETHOD(setPLUPrintFormat)(LONG printFormat);
	STDMETHOD(getException)(BSTR* exception);
	STDMETHOD(setSleep)(LONG sleep);
	STDMETHOD(addPLUToQueue)();
	STDMETHOD(setTime)(LONG year, LONG month, LONG day, LONG hour, LONG minute, LONG seconds);
	STDMETHOD(clearPLU)(LONG number);
	STDMETHOD(getTime)(BSTR* time);
	STDMETHOD(setKeyPage)(LONG page);
	STDMETHOD(addPLUKeyToQueue)();
	STDMETHOD(getScalesAccaunt)(LONG number, BSTR* accaunt);
	STDMETHOD(getSummedScalesAccaunt)(LONG number, BSTR* accaunt);
	STDMETHOD(getInfo)(BSTR* info);
	STDMETHOD(getMac)(BSTR* mac);
	STDMETHOD(disconnect)();
	STDMETHOD(readTMAFile)(BSTR* file);
	STDMETHODIMP sendConstTMT1(BSTR value, BSTR* result) override
	{
		// Конвертуємо BSTR в std::string і зберігаємо
		m_shopName = ConvertBSTRToString(value);
		return sendConstTMT(0, value, result);
	}
	STDMETHODIMP sendConstTMT2(BSTR value, BSTR* result) override
	{
		// Конвертуємо BSTR в std::string і зберігаємо
		m_shopName = ConvertBSTRToString(value);
		return sendConstTMT(0, value, result);
	}
	STDMETHODIMP sendConstTMT3(BSTR value, BSTR* result) override
	{
		// Конвертуємо BSTR в std::string і зберігаємо
		m_shopName = ConvertBSTRToString(value);
		return sendConstTMT(0, value, result);
	}
	STDMETHOD(sendConstTMT)(LONG fieldNumber, BSTR value, BSTR* result);
	STDMETHOD(uploadTMTToScales)();
};

OBJECT_ENTRY_AUTO(__uuidof(Connector), CConnector)
