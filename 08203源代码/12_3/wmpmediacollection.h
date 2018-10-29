#if !defined(AFX_WMPMEDIACOLLECTION_H__D1185DB1_1A4A_40BC_AA1F_9FA27D0FF2CA__INCLUDED_)
#define AFX_WMPMEDIACOLLECTION_H__D1185DB1_1A4A_40BC_AA1F_9FA27D0FF2CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CWMPMedia;
class CWMPPlaylist;
class CWMPStringCollection;

/////////////////////////////////////////////////////////////////////////////
// CWMPMediaCollection wrapper class

class CWMPMediaCollection : public COleDispatchDriver
{
public:
	CWMPMediaCollection() {}		// Calls COleDispatchDriver default constructor
	CWMPMediaCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPMediaCollection(const CWMPMediaCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CWMPMedia add(LPCTSTR bstrURL);
	CWMPPlaylist getAll();
	CWMPPlaylist getByName(LPCTSTR bstrName);
	CWMPPlaylist getByGenre(LPCTSTR bstrGenre);
	CWMPPlaylist getByAuthor(LPCTSTR bstrAuthor);
	CWMPPlaylist getByAlbum(LPCTSTR bstrAlbum);
	CWMPPlaylist getByAttribute(LPCTSTR bstrAttribute, LPCTSTR bstrValue);
	void remove(LPDISPATCH pItem, BOOL varfDeleteFile);
	CWMPStringCollection getAttributeStringCollection(LPCTSTR bstrAttribute, LPCTSTR bstrMediaType);
	long getMediaAtom(LPCTSTR bstrItemName);
	void setDeleted(LPDISPATCH pItem, BOOL varfIsDeleted);
	BOOL isDeleted(LPDISPATCH pItem);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMPMEDIACOLLECTION_H__D1185DB1_1A4A_40BC_AA1F_9FA27D0FF2CA__INCLUDED_)
