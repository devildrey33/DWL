/*! \file DWL_ITASKBAR.h
	\brief Cabecera de compatibilidad para los objetos com ITaskBar3 y ITaskBar4.
*/ 

#ifndef DWL_ITASKBAR
#define DWL_ITASKBAR
	#include "DWL.h"
	#if COMPILADOR == COMPILADOR_VC6
		#include "UNKNWN.h"
//#include "rpcndr.h"
//		#define MIDL_INTERFACE(x)   struct DECLSPEC_UUID(x) DECLSPEC_NOVTABLE
//		#define MIDL_INTERFACE(x)   struct __declspec(uuid(x)) __declspec(novtable)

		#define __RPC__in
		#define __RPC__in_ecount_full(size)
		#define __RPC__in_opt
		#define __RPC__in_opt_string

		const GUID 	CLSID_TaskbarList = { 0x56FDF344,0xFD6D,0x11d0,{0x95,0x8A,0x00,0x60,0x97,0xC9,0xA0,0x90}};

		// ITaskBar1 ITaskBar2
		#ifndef __ITaskbarList_INTERFACE_DEFINED__
		#define __ITaskbarList_INTERFACE_DEFINED__

		/* interface ITaskbarList */
		/* [object][uuid] */ 

//		typedef struct _IUnknown IUnknown;
//		EXTERN_C const IID IID_ITaskbarList;

		#if defined(__cplusplus) && !defined(CINTERFACE)
    
			struct __declspec(uuid("56FDF342-FD6D-11d0-958A-006097C9A090")) __declspec(novtable)
			ITaskbarList : public IUnknown
			{
			public:
				virtual HRESULT STDMETHODCALLTYPE HrInit( void) = 0;
        
				virtual HRESULT STDMETHODCALLTYPE AddTab( 
					/* [in] */ __RPC__in HWND hwnd) = 0;
        
				virtual HRESULT STDMETHODCALLTYPE DeleteTab( 
					/* [in] */ __RPC__in HWND hwnd) = 0;
        
				virtual HRESULT STDMETHODCALLTYPE ActivateTab( 
					/* [in] */ __RPC__in HWND hwnd) = 0;
        
				virtual HRESULT STDMETHODCALLTYPE SetActiveAlt( 
					/* [in] */ __RPC__in HWND hwnd) = 0;
        
			};
    
		#else 	/* C style interface */

			typedef struct ITaskbarListVtbl
			{
				BEGIN_INTERFACE
        
				HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
					__RPC__in ITaskbarList * This,
					/* [in] */ __RPC__in REFIID riid,
					/* [annotation][iid_is][out] */ 
					__RPC__deref_out  void **ppvObject);
        
				ULONG ( STDMETHODCALLTYPE *AddRef )( 
					__RPC__in ITaskbarList * This);
        
				ULONG ( STDMETHODCALLTYPE *Release )( 
					__RPC__in ITaskbarList * This);
        
				HRESULT ( STDMETHODCALLTYPE *HrInit )( 
					__RPC__in ITaskbarList * This);
        
				HRESULT ( STDMETHODCALLTYPE *AddTab )( 
					__RPC__in ITaskbarList * This,
					/* [in] */ __RPC__in HWND hwnd);
        
				HRESULT ( STDMETHODCALLTYPE *DeleteTab )( 
					__RPC__in ITaskbarList * This,
					/* [in] */ __RPC__in HWND hwnd);
        
				HRESULT ( STDMETHODCALLTYPE *ActivateTab )( 
					__RPC__in ITaskbarList * This,
					/* [in] */ __RPC__in HWND hwnd);
        
				HRESULT ( STDMETHODCALLTYPE *SetActiveAlt )( 
					__RPC__in ITaskbarList * This,
					/* [in] */ __RPC__in HWND hwnd);
        
				END_INTERFACE
			} ITaskbarListVtbl;

			interface ITaskbarList
			{
				CONST_VTBL struct ITaskbarListVtbl *lpVtbl;
			};

    

		#ifdef COBJMACROS


		#define ITaskbarList_QueryInterface(This,riid,ppvObject)	\
			( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

		#define ITaskbarList_AddRef(This)	\
			( (This)->lpVtbl -> AddRef(This) ) 

		#define ITaskbarList_Release(This)	\
			( (This)->lpVtbl -> Release(This) ) 


		#define ITaskbarList_HrInit(This)	\
			( (This)->lpVtbl -> HrInit(This) ) 

		#define ITaskbarList_AddTab(This,hwnd)	\
			( (This)->lpVtbl -> AddTab(This,hwnd) ) 

		#define ITaskbarList_DeleteTab(This,hwnd)	\
			( (This)->lpVtbl -> DeleteTab(This,hwnd) ) 

		#define ITaskbarList_ActivateTab(This,hwnd)	\
			( (This)->lpVtbl -> ActivateTab(This,hwnd) ) 

		#define ITaskbarList_SetActiveAlt(This,hwnd)	\
			( (This)->lpVtbl -> SetActiveAlt(This,hwnd) ) 

		#endif /* COBJMACROS */


		#endif 	/* C style interface */




		#endif 	/* __ITaskbarList_INTERFACE_DEFINED__ */


		#ifndef __ITaskbarList2_INTERFACE_DEFINED__
		#define __ITaskbarList2_INTERFACE_DEFINED__

		/* interface ITaskbarList2 */
		/* [object][uuid] */ 


		EXTERN_C const IID IID_ITaskbarList2;

		#if defined(__cplusplus) && !defined(CINTERFACE)
    
			MIDL_INTERFACE("602D4995-B13A-429b-A66E-1935E44F4317")
			ITaskbarList2 : public ITaskbarList
			{
			public:
				virtual HRESULT STDMETHODCALLTYPE MarkFullscreenWindow( 
					/* [in] */ __RPC__in HWND hwnd,
					/* [in] */ BOOL fFullscreen) = 0;
        
			};
    
		#else 	/* C style interface */

			typedef struct ITaskbarList2Vtbl
			{
				BEGIN_INTERFACE
        
				HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
					__RPC__in ITaskbarList2 * This,
					/* [in] */ __RPC__in REFIID riid,
					/* [annotation][iid_is][out] */ 
					__RPC__deref_out  void **ppvObject);
        
				ULONG ( STDMETHODCALLTYPE *AddRef )( 
					__RPC__in ITaskbarList2 * This);
        
				ULONG ( STDMETHODCALLTYPE *Release )( 
					__RPC__in ITaskbarList2 * This);
        
				HRESULT ( STDMETHODCALLTYPE *HrInit )( 
					__RPC__in ITaskbarList2 * This);
        
				HRESULT ( STDMETHODCALLTYPE *AddTab )( 
					__RPC__in ITaskbarList2 * This,
					/* [in] */ __RPC__in HWND hwnd);
        
				HRESULT ( STDMETHODCALLTYPE *DeleteTab )( 
					__RPC__in ITaskbarList2 * This,
					/* [in] */ __RPC__in HWND hwnd);
        
				HRESULT ( STDMETHODCALLTYPE *ActivateTab )( 
					__RPC__in ITaskbarList2 * This,
					/* [in] */ __RPC__in HWND hwnd);
        
				HRESULT ( STDMETHODCALLTYPE *SetActiveAlt )( 
					__RPC__in ITaskbarList2 * This,
					/* [in] */ __RPC__in HWND hwnd);
        
				HRESULT ( STDMETHODCALLTYPE *MarkFullscreenWindow )( 
					__RPC__in ITaskbarList2 * This,
					/* [in] */ __RPC__in HWND hwnd,
					/* [in] */ BOOL fFullscreen);
        
				END_INTERFACE
			} ITaskbarList2Vtbl;

			interface ITaskbarList2
			{
				CONST_VTBL struct ITaskbarList2Vtbl *lpVtbl;
			};

    

		#ifdef COBJMACROS


		#define ITaskbarList2_QueryInterface(This,riid,ppvObject)	\
			( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

		#define ITaskbarList2_AddRef(This)	\
			( (This)->lpVtbl -> AddRef(This) ) 

		#define ITaskbarList2_Release(This)	\
			( (This)->lpVtbl -> Release(This) ) 


		#define ITaskbarList2_HrInit(This)	\
			( (This)->lpVtbl -> HrInit(This) ) 

		#define ITaskbarList2_AddTab(This,hwnd)	\
			( (This)->lpVtbl -> AddTab(This,hwnd) ) 

		#define ITaskbarList2_DeleteTab(This,hwnd)	\
			( (This)->lpVtbl -> DeleteTab(This,hwnd) ) 

		#define ITaskbarList2_ActivateTab(This,hwnd)	\
			( (This)->lpVtbl -> ActivateTab(This,hwnd) ) 

		#define ITaskbarList2_SetActiveAlt(This,hwnd)	\
			( (This)->lpVtbl -> SetActiveAlt(This,hwnd) ) 


		#define ITaskbarList2_MarkFullscreenWindow(This,hwnd,fFullscreen)	\
			( (This)->lpVtbl -> MarkFullscreenWindow(This,hwnd,fFullscreen) ) 

		#endif /* COBJMACROS */


		#endif 	/* C style interface */




		#endif 	/* __ITaskbarList2_INTERFACE_DEFINED__ */
	#endif // VC6










	// ITaskBar 3 y 4
	#ifdef __cplusplus
		// Define operator overloads to enable bit operations on enum values that are 
		// used to define flags. Use DEFINE_ENUM_FLAG_OPERATORS(YOUR_TYPE) to enable these 
		// operators on YOUR_TYPE.

		// Moved here from objbase.w.
		#define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) \
		extern "C++" { \
		inline ENUMTYPE operator | (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) | ((int)b)); } \
		inline ENUMTYPE &operator |= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) |= ((int)b)); } \
		inline ENUMTYPE operator & (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) & ((int)b)); } \
		inline ENUMTYPE &operator &= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) &= ((int)b)); } \
		inline ENUMTYPE operator ~ (ENUMTYPE a) { return ENUMTYPE(~((int)a)); } \
		inline ENUMTYPE operator ^ (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) ^ ((int)b)); } \
		inline ENUMTYPE &operator ^= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) ^= ((int)b)); } \
		}
	#else
		#define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) // NOP, C allows these operators.
	#endif




	#ifndef __ITaskbarList3_FWD_DEFINED__
	#define __ITaskbarList3_FWD_DEFINED__
	typedef interface ITaskbarList3 ITaskbarList3;
	#endif 	/* __ITaskbarList3_FWD_DEFINED__ */

	#ifndef __ITaskbarList4_FWD_DEFINED__
	#define __ITaskbarList4_FWD_DEFINED__
	typedef interface ITaskbarList4 ITaskbarList4;
	#endif 	/* __ITaskbarList4_FWD_DEFINED__ */

	/* interface __MIDL_itf_shobjidl_0000_0093 */
	/* [local] */ 

	#ifdef MIDL_PASS
	typedef IUnknown *HIMAGELIST;

	#endif
	typedef /* [v1_enum] */ 
	enum THUMBBUTTONFLAGS
		{	THBF_ENABLED	= 0,
		THBF_DISABLED	= 0x1,
		THBF_DISMISSONCLICK	= 0x2,
		THBF_NOBACKGROUND	= 0x4,
		THBF_HIDDEN	= 0x8,
		THBF_NONINTERACTIVE	= 0x10
		} 	THUMBBUTTONFLAGS;

	DEFINE_ENUM_FLAG_OPERATORS(THUMBBUTTONFLAGS)
	typedef /* [v1_enum] */ 
	enum THUMBBUTTONMASK
		{	THB_BITMAP	= 0x1,
		THB_ICON	= 0x2,
		THB_TOOLTIP	= 0x4,
		THB_FLAGS	= 0x8
		} 	THUMBBUTTONMASK;

	DEFINE_ENUM_FLAG_OPERATORS(THUMBBUTTONMASK)
	#include <pshpack8.h>
	typedef struct THUMBBUTTON
		{
		THUMBBUTTONMASK dwMask;
		UINT iId;
		UINT iBitmap;
		HICON hIcon;
		WCHAR szTip[ 260 ];
		THUMBBUTTONFLAGS dwFlags;
		} 	THUMBBUTTON;

	typedef struct THUMBBUTTON *LPTHUMBBUTTON;

	#include <poppack.h>
	#define THBN_CLICKED        0x1800


//		extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0000_0093_v0_0_c_ifspec;
//		extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0000_0093_v0_0_s_ifspec;

	#ifndef __ITaskbarList3_INTERFACE_DEFINED__
	#define __ITaskbarList3_INTERFACE_DEFINED__

	/* interface ITaskbarList3 */
	/* [object][uuid] */ 

	typedef /* [v1_enum] */ 
	enum TBPFLAG
		{	TBPF_NOPROGRESS	= 0,
		TBPF_INDETERMINATE	= 0x1,
		TBPF_NORMAL	= 0x2,
		TBPF_ERROR	= 0x4,
		TBPF_PAUSED	= 0x8
		} 	TBPFLAG;

	DEFINE_ENUM_FLAG_OPERATORS(TBPFLAG)

//		EXTERN_C const IID IID_ITaskbarList3;
	const GUID IID_ITaskbarList3 = { 0xea1afb91,0x9e28,0x4b86,{0x90,0xe9,0x9e,0x9f,0x8a,0x5e,0xef,0xaf}};

	#if defined(__cplusplus) && !defined(CINTERFACE)

		MIDL_INTERFACE("ea1afb91-9e28-4b86-90e9-9e9f8a5eefaf")
		ITaskbarList3 : public ITaskbarList2
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE SetProgressValue( 
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ ULONGLONG ullCompleted,
				/* [in] */ ULONGLONG ullTotal) = 0;
    
			virtual HRESULT STDMETHODCALLTYPE SetProgressState( 
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ TBPFLAG tbpFlags) = 0;
    
			virtual HRESULT STDMETHODCALLTYPE RegisterTab( 
				/* [in] */ __RPC__in HWND hwndTab,
				/* [in] */ __RPC__in HWND hwndMDI) = 0;
    
			virtual HRESULT STDMETHODCALLTYPE UnregisterTab( 
				/* [in] */ __RPC__in HWND hwndTab) = 0;
    
			virtual HRESULT STDMETHODCALLTYPE SetTabOrder( 
				/* [in] */ __RPC__in HWND hwndTab,
				/* [in] */ __RPC__in HWND hwndInsertBefore) = 0;
    
			virtual HRESULT STDMETHODCALLTYPE SetTabActive( 
				/* [in] */ __RPC__in HWND hwndTab,
				/* [in] */ __RPC__in HWND hwndMDI,
				/* [in] */ DWORD dwReserved) = 0;
    
			virtual HRESULT STDMETHODCALLTYPE ThumbBarAddButtons( 
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ UINT cButtons,
				/* [size_is][in] */ __RPC__in_ecount_full(cButtons) LPTHUMBBUTTON pButton) = 0;
    
			virtual HRESULT STDMETHODCALLTYPE ThumbBarUpdateButtons( 
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ UINT cButtons,
				/* [size_is][in] */ __RPC__in_ecount_full(cButtons) LPTHUMBBUTTON pButton) = 0;
    
			virtual HRESULT STDMETHODCALLTYPE ThumbBarSetImageList( 
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ __RPC__in_opt HIMAGELIST himl) = 0;
    
			virtual HRESULT STDMETHODCALLTYPE SetOverlayIcon( 
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ __RPC__in HICON hIcon,
				/* [string][unique][in] */ __RPC__in_opt_string LPCWSTR pszDescription) = 0;
    
			virtual HRESULT STDMETHODCALLTYPE SetThumbnailTooltip( 
				/* [in] */ __RPC__in HWND hwnd,
				/* [string][unique][in] */ __RPC__in_opt_string LPCWSTR pszTip) = 0;
    
			virtual HRESULT STDMETHODCALLTYPE SetThumbnailClip( 
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ __RPC__in RECT *prcClip) = 0;
    
		};

	#else 	/* C style interface */

		typedef struct ITaskbarList3Vtbl
		{
			BEGIN_INTERFACE
    
			HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in REFIID riid,
				/* [annotation][iid_is][out] */ 
				__RPC__deref_out  void **ppvObject);
    
			ULONG ( STDMETHODCALLTYPE *AddRef )( 
				__RPC__in ITaskbarList3 * This);
    
			ULONG ( STDMETHODCALLTYPE *Release )( 
				__RPC__in ITaskbarList3 * This);
    
			HRESULT ( STDMETHODCALLTYPE *HrInit )( 
				__RPC__in ITaskbarList3 * This);
    
			HRESULT ( STDMETHODCALLTYPE *AddTab )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd);
    
			HRESULT ( STDMETHODCALLTYPE *DeleteTab )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd);
    
			HRESULT ( STDMETHODCALLTYPE *ActivateTab )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd);
    
			HRESULT ( STDMETHODCALLTYPE *SetActiveAlt )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd);
    
			HRESULT ( STDMETHODCALLTYPE *MarkFullscreenWindow )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ BOOL fFullscreen);
    
			HRESULT ( STDMETHODCALLTYPE *SetProgressValue )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ ULONGLONG ullCompleted,
				/* [in] */ ULONGLONG ullTotal);
    
			HRESULT ( STDMETHODCALLTYPE *SetProgressState )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ TBPFLAG tbpFlags);
    
			HRESULT ( STDMETHODCALLTYPE *RegisterTab )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwndTab,
				/* [in] */ __RPC__in HWND hwndMDI);
    
			HRESULT ( STDMETHODCALLTYPE *UnregisterTab )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwndTab);
    
			HRESULT ( STDMETHODCALLTYPE *SetTabOrder )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwndTab,
				/* [in] */ __RPC__in HWND hwndInsertBefore);
    
			HRESULT ( STDMETHODCALLTYPE *SetTabActive )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwndTab,
				/* [in] */ __RPC__in HWND hwndMDI,
				/* [in] */ DWORD dwReserved);
    
			HRESULT ( STDMETHODCALLTYPE *ThumbBarAddButtons )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ UINT cButtons,
				/* [size_is][in] */ __RPC__in_ecount_full(cButtons) LPTHUMBBUTTON pButton);
    
			HRESULT ( STDMETHODCALLTYPE *ThumbBarUpdateButtons )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ UINT cButtons,
				/* [size_is][in] */ __RPC__in_ecount_full(cButtons) LPTHUMBBUTTON pButton);
    
			HRESULT ( STDMETHODCALLTYPE *ThumbBarSetImageList )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ __RPC__in_opt HIMAGELIST himl);
    
			HRESULT ( STDMETHODCALLTYPE *SetOverlayIcon )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ __RPC__in HICON hIcon,
				/* [string][unique][in] */ __RPC__in_opt_string LPCWSTR pszDescription);
    
			HRESULT ( STDMETHODCALLTYPE *SetThumbnailTooltip )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [string][unique][in] */ __RPC__in_opt_string LPCWSTR pszTip);
    
			HRESULT ( STDMETHODCALLTYPE *SetThumbnailClip )( 
				__RPC__in ITaskbarList3 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ __RPC__in RECT *prcClip);
    
			END_INTERFACE
		} ITaskbarList3Vtbl;

		interface ITaskbarList3
		{
			CONST_VTBL struct ITaskbarList3Vtbl *lpVtbl;
		};



	#ifdef COBJMACROS


	#define ITaskbarList3_QueryInterface(This,riid,ppvObject)	\
		( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

	#define ITaskbarList3_AddRef(This)	\
		( (This)->lpVtbl -> AddRef(This) ) 

	#define ITaskbarList3_Release(This)	\
		( (This)->lpVtbl -> Release(This) ) 


	#define ITaskbarList3_HrInit(This)	\
		( (This)->lpVtbl -> HrInit(This) ) 

	#define ITaskbarList3_AddTab(This,hwnd)	\
		( (This)->lpVtbl -> AddTab(This,hwnd) ) 

	#define ITaskbarList3_DeleteTab(This,hwnd)	\
		( (This)->lpVtbl -> DeleteTab(This,hwnd) ) 

	#define ITaskbarList3_ActivateTab(This,hwnd)	\
		( (This)->lpVtbl -> ActivateTab(This,hwnd) ) 

	#define ITaskbarList3_SetActiveAlt(This,hwnd)	\
		( (This)->lpVtbl -> SetActiveAlt(This,hwnd) ) 


	#define ITaskbarList3_MarkFullscreenWindow(This,hwnd,fFullscreen)	\
		( (This)->lpVtbl -> MarkFullscreenWindow(This,hwnd,fFullscreen) ) 


	#define ITaskbarList3_SetProgressValue(This,hwnd,ullCompleted,ullTotal)	\
		( (This)->lpVtbl -> SetProgressValue(This,hwnd,ullCompleted,ullTotal) ) 

	#define ITaskbarList3_SetProgressState(This,hwnd,tbpFlags)	\
		( (This)->lpVtbl -> SetProgressState(This,hwnd,tbpFlags) ) 

	#define ITaskbarList3_RegisterTab(This,hwndTab,hwndMDI)	\
		( (This)->lpVtbl -> RegisterTab(This,hwndTab,hwndMDI) ) 

	#define ITaskbarList3_UnregisterTab(This,hwndTab)	\
		( (This)->lpVtbl -> UnregisterTab(This,hwndTab) ) 

	#define ITaskbarList3_SetTabOrder(This,hwndTab,hwndInsertBefore)	\
		( (This)->lpVtbl -> SetTabOrder(This,hwndTab,hwndInsertBefore) ) 

	#define ITaskbarList3_SetTabActive(This,hwndTab,hwndMDI,dwReserved)	\
		( (This)->lpVtbl -> SetTabActive(This,hwndTab,hwndMDI,dwReserved) ) 

	#define ITaskbarList3_ThumbBarAddButtons(This,hwnd,cButtons,pButton)	\
		( (This)->lpVtbl -> ThumbBarAddButtons(This,hwnd,cButtons,pButton) ) 

	#define ITaskbarList3_ThumbBarUpdateButtons(This,hwnd,cButtons,pButton)	\
		( (This)->lpVtbl -> ThumbBarUpdateButtons(This,hwnd,cButtons,pButton) ) 

	#define ITaskbarList3_ThumbBarSetImageList(This,hwnd,himl)	\
		( (This)->lpVtbl -> ThumbBarSetImageList(This,hwnd,himl) ) 

	#define ITaskbarList3_SetOverlayIcon(This,hwnd,hIcon,pszDescription)	\
		( (This)->lpVtbl -> SetOverlayIcon(This,hwnd,hIcon,pszDescription) ) 

	#define ITaskbarList3_SetThumbnailTooltip(This,hwnd,pszTip)	\
		( (This)->lpVtbl -> SetThumbnailTooltip(This,hwnd,pszTip) ) 

	#define ITaskbarList3_SetThumbnailClip(This,hwnd,prcClip)	\
		( (This)->lpVtbl -> SetThumbnailClip(This,hwnd,prcClip) ) 

	#endif /* COBJMACROS */


	#endif 	/* C style interface */




	#endif 	/* __ITaskbarList3_INTERFACE_DEFINED__ */


	#ifndef __ITaskbarList4_INTERFACE_DEFINED__
	#define __ITaskbarList4_INTERFACE_DEFINED__

	/* interface ITaskbarList4 */
	/* [object][uuid] */ 

	typedef /* [v1_enum] */ 
	enum STPFLAG
		{	STPF_NONE	= 0,
		STPF_USEAPPTHUMBNAILALWAYS	= 0x1,
		STPF_USEAPPTHUMBNAILWHENACTIVE	= 0x2,
		STPF_USEAPPPEEKALWAYS	= 0x4,
		STPF_USEAPPPEEKWHENACTIVE	= 0x8
		} 	STPFLAG;

	DEFINE_ENUM_FLAG_OPERATORS(STPFLAG)

	EXTERN_C const IID IID_ITaskbarList4;

	#if defined(__cplusplus) && !defined(CINTERFACE)

		MIDL_INTERFACE("c43dc798-95d1-4bea-9030-bb99e2983a1a")
		ITaskbarList4 : public ITaskbarList3
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE SetTabProperties( 
				/* [in] */ __RPC__in HWND hwndTab,
				/* [in] */ STPFLAG stpFlags) = 0;
    
		};

	#else 	/* C style interface */

		typedef struct ITaskbarList4Vtbl
		{
			BEGIN_INTERFACE
    
			HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in REFIID riid,
				/* [annotation][iid_is][out] */ 
				__RPC__deref_out  void **ppvObject);
    
			ULONG ( STDMETHODCALLTYPE *AddRef )( 
				__RPC__in ITaskbarList4 * This);
    
			ULONG ( STDMETHODCALLTYPE *Release )( 
				__RPC__in ITaskbarList4 * This);
    
			HRESULT ( STDMETHODCALLTYPE *HrInit )( 
				__RPC__in ITaskbarList4 * This);
    
			HRESULT ( STDMETHODCALLTYPE *AddTab )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd);
    
			HRESULT ( STDMETHODCALLTYPE *DeleteTab )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd);
    
			HRESULT ( STDMETHODCALLTYPE *ActivateTab )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd);
    
			HRESULT ( STDMETHODCALLTYPE *SetActiveAlt )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd);
    
			HRESULT ( STDMETHODCALLTYPE *MarkFullscreenWindow )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ BOOL fFullscreen);
    
			HRESULT ( STDMETHODCALLTYPE *SetProgressValue )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ ULONGLONG ullCompleted,
				/* [in] */ ULONGLONG ullTotal);
    
			HRESULT ( STDMETHODCALLTYPE *SetProgressState )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ TBPFLAG tbpFlags);
    
			HRESULT ( STDMETHODCALLTYPE *RegisterTab )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwndTab,
				/* [in] */ __RPC__in HWND hwndMDI);
    
			HRESULT ( STDMETHODCALLTYPE *UnregisterTab )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwndTab);
    
			HRESULT ( STDMETHODCALLTYPE *SetTabOrder )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwndTab,
				/* [in] */ __RPC__in HWND hwndInsertBefore);
    
			HRESULT ( STDMETHODCALLTYPE *SetTabActive )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwndTab,
				/* [in] */ __RPC__in HWND hwndMDI,
				/* [in] */ DWORD dwReserved);
    
			HRESULT ( STDMETHODCALLTYPE *ThumbBarAddButtons )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ UINT cButtons,
				/* [size_is][in] */ __RPC__in_ecount_full(cButtons) LPTHUMBBUTTON pButton);
    
			HRESULT ( STDMETHODCALLTYPE *ThumbBarUpdateButtons )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ UINT cButtons,
				/* [size_is][in] */ __RPC__in_ecount_full(cButtons) LPTHUMBBUTTON pButton);
    
			HRESULT ( STDMETHODCALLTYPE *ThumbBarSetImageList )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ __RPC__in_opt HIMAGELIST himl);
    
			HRESULT ( STDMETHODCALLTYPE *SetOverlayIcon )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ __RPC__in HICON hIcon,
				/* [string][unique][in] */ __RPC__in_opt_string LPCWSTR pszDescription);
    
			HRESULT ( STDMETHODCALLTYPE *SetThumbnailTooltip )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [string][unique][in] */ __RPC__in_opt_string LPCWSTR pszTip);
    
			HRESULT ( STDMETHODCALLTYPE *SetThumbnailClip )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwnd,
				/* [in] */ __RPC__in RECT *prcClip);
    
			HRESULT ( STDMETHODCALLTYPE *SetTabProperties )( 
				__RPC__in ITaskbarList4 * This,
				/* [in] */ __RPC__in HWND hwndTab,
				/* [in] */ STPFLAG stpFlags);
    
			END_INTERFACE
		} ITaskbarList4Vtbl;

		interface ITaskbarList4
		{
			CONST_VTBL struct ITaskbarList4Vtbl *lpVtbl;
		};



	#ifdef COBJMACROS


	#define ITaskbarList4_QueryInterface(This,riid,ppvObject)	\
		( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

	#define ITaskbarList4_AddRef(This)	\
		( (This)->lpVtbl -> AddRef(This) ) 

	#define ITaskbarList4_Release(This)	\
		( (This)->lpVtbl -> Release(This) ) 


	#define ITaskbarList4_HrInit(This)	\
		( (This)->lpVtbl -> HrInit(This) ) 

	#define ITaskbarList4_AddTab(This,hwnd)	\
		( (This)->lpVtbl -> AddTab(This,hwnd) ) 

	#define ITaskbarList4_DeleteTab(This,hwnd)	\
		( (This)->lpVtbl -> DeleteTab(This,hwnd) ) 

	#define ITaskbarList4_ActivateTab(This,hwnd)	\
		( (This)->lpVtbl -> ActivateTab(This,hwnd) ) 

	#define ITaskbarList4_SetActiveAlt(This,hwnd)	\
		( (This)->lpVtbl -> SetActiveAlt(This,hwnd) ) 


	#define ITaskbarList4_MarkFullscreenWindow(This,hwnd,fFullscreen)	\
		( (This)->lpVtbl -> MarkFullscreenWindow(This,hwnd,fFullscreen) ) 


	#define ITaskbarList4_SetProgressValue(This,hwnd,ullCompleted,ullTotal)	\
		( (This)->lpVtbl -> SetProgressValue(This,hwnd,ullCompleted,ullTotal) ) 

	#define ITaskbarList4_SetProgressState(This,hwnd,tbpFlags)	\
		( (This)->lpVtbl -> SetProgressState(This,hwnd,tbpFlags) ) 

	#define ITaskbarList4_RegisterTab(This,hwndTab,hwndMDI)	\
		( (This)->lpVtbl -> RegisterTab(This,hwndTab,hwndMDI) ) 

	#define ITaskbarList4_UnregisterTab(This,hwndTab)	\
		( (This)->lpVtbl -> UnregisterTab(This,hwndTab) ) 

	#define ITaskbarList4_SetTabOrder(This,hwndTab,hwndInsertBefore)	\
		( (This)->lpVtbl -> SetTabOrder(This,hwndTab,hwndInsertBefore) ) 

	#define ITaskbarList4_SetTabActive(This,hwndTab,hwndMDI,dwReserved)	\
		( (This)->lpVtbl -> SetTabActive(This,hwndTab,hwndMDI,dwReserved) ) 

	#define ITaskbarList4_ThumbBarAddButtons(This,hwnd,cButtons,pButton)	\
		( (This)->lpVtbl -> ThumbBarAddButtons(This,hwnd,cButtons,pButton) ) 

	#define ITaskbarList4_ThumbBarUpdateButtons(This,hwnd,cButtons,pButton)	\
		( (This)->lpVtbl -> ThumbBarUpdateButtons(This,hwnd,cButtons,pButton) ) 

	#define ITaskbarList4_ThumbBarSetImageList(This,hwnd,himl)	\
		( (This)->lpVtbl -> ThumbBarSetImageList(This,hwnd,himl) ) 

	#define ITaskbarList4_SetOverlayIcon(This,hwnd,hIcon,pszDescription)	\
		( (This)->lpVtbl -> SetOverlayIcon(This,hwnd,hIcon,pszDescription) ) 

	#define ITaskbarList4_SetThumbnailTooltip(This,hwnd,pszTip)	\
		( (This)->lpVtbl -> SetThumbnailTooltip(This,hwnd,pszTip) ) 

	#define ITaskbarList4_SetThumbnailClip(This,hwnd,prcClip)	\
		( (This)->lpVtbl -> SetThumbnailClip(This,hwnd,prcClip) ) 


	#define ITaskbarList4_SetTabProperties(This,hwndTab,stpFlags)	\
		( (This)->lpVtbl -> SetTabProperties(This,hwndTab,stpFlags) ) 

	#endif /* COBJMACROS */


	#endif 	/* C style interface */




	#endif 	/* __ITaskbarList4_INTERFACE_DEFINED__ */

#endif