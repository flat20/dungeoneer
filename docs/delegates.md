	from DelegateSignatureImpl.inl
    
    /**
	 * Adds a raw C++ pointer global function delegate
	 *
	 * @param	InFunc	Function pointer
	 */
	template <typename... VarTypes>
	inline FDelegateHandle AddStatic(typename TBaseStaticDelegateInstance<void (ParamTypes...), VarTypes...>::FFuncPtr InFunc, VarTypes... Vars)
	{
		return Add(FDelegate::CreateStatic(InFunc, Vars...));
	}