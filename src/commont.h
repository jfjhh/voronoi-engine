/**
 * Useful Templates.
 * Alex Striff.
 */

#ifndef COMMONT_H
#define COMMONT_H

#include <type_traits>

#define COMMON_VERIFY_BASIC(CLASS) \
static_assert(std::is_destructible< CLASS >(), \
		"COMMON: " #CLASS " objects are not destructible!")

#define COMMON_VERIFY_MOVE(CLASS) \
	COMMON_VERIFY_BASIC(CLASS); \
static_assert(std::is_move_constructible< CLASS >(), \
		"COMMON: " #CLASS " objects are not move-constructible!"); \
static_assert(std::is_move_assignable< CLASS >(), \
		"COMMON: " #CLASS " objects are not move-assignable!")

#define COMMON_VERIFY(CLASS) \
	COMMON_VERIFY_MOVE(CLASS); \
static_assert(std::is_copy_constructible< CLASS >(), \
		"COMMON: " #CLASS " objects are not copy-constructible!"); \
static_assert(std::is_copy_assignable< CLASS >(), \
		"COMMON: " #CLASS " objects are not copy-assignable!")

namespace voronoi
{
	/*******************************************************************
	 * Mini STL <type_traits>-like templates for learning TMP.         *
	 ******************************************************************/
	template<class T> struct type_is { using type = T; };

	template<class...> using void_t = void;

	template<class T, T v>
		struct integral_constant {
			static constexpr T value = v;
			using value_type = T;
			using type       = integral_constant<T, v>;
			constexpr   operator  T(void) const noexcept { return value; }
			constexpr T operator ()(void) const noexcept { return value; }
		};
	template<class T, T v> using integral_constant_t
		= typename integral_constant<T, v>::type;
	template<class T, T v> using integral_constant_tv
		= typename integral_constant<T, v>::value_type;

	template<bool b> using bool_constant = integral_constant<bool, b>;
	template<bool b> using bool_constant_t
		= typename bool_constant<b>::type;
	using bool_constant_tv = bool;

	using true_type     = bool_constant<true>;
	using true_type_t   = typename bool_constant<true>::type;
	using true_type_tv  = bool;
	using false_type    = bool_constant<false>;
	using false_type_t  = typename bool_constant<false>::type;
	using false_type_tv = bool;

	template<class T, class U> struct is_same       : false_type {};
	template<class T>          struct is_same<T, T> : true_type  {};
	template<class T, class U> using is_same_t = typename is_same<T, U>::type;

	template<class T, class... L> struct is_one_of;
	template<class T>             struct is_one_of<T> : false_type {};
	template<class T, class... L> struct is_one_of<T, T, L...> : true_type {};
	template<class T, class U, class... L>
		struct is_one_of<T, U, L...> : is_one_of<T, L...> {};
	template<class T, class... L> using is_one_of_t
		= typename is_one_of<T, L...>::type;

	template<bool, class T, class> struct IF              : type_is<T> {};
	template<class T, class F>     struct IF<false, T, F> : type_is<F> {};
	template<bool B, class T, class F> using IF_t
		= typename IF<B, T, F>::type;

	template<bool, class T = void> struct enable_if {};
	template<class T>              struct enable_if<true, T> : type_is<T> {};
	template<bool B, class T> using enable_if_t
		= typename enable_if<B, T>::type;

	template<class, class T = void> struct enable_bool_constant {};
	template<class T>
		struct enable_bool_constant<true_type, T> : type_is<T> {};
	template<class T> using enable_bool_constant_t
		= typename enable_bool_constant<T>::type;

	template<class, class = void> struct is_well_formed : false_type {};
	template<class T> struct is_well_formed<T, void_t<T>> : true_type {};
	template<class T> using is_well_formed_t = typename is_well_formed<T>::type;

	template<class T> using is_bool_constant = is_well_formed<
		decltype(std::declval<bool>() = std::declval<T::value>())>;
	template<class T> using is_well_formed_t = typename is_well_formed<T>::type;

	template<class T> using has_type_member
		= is_well_formed<typename T::type>;
	template<class T> using has_type_member_t
		= typename has_type_member<T>::type;

	template<class T> using has_value_member
		= is_well_formed<typename T::value>;
	template<class T> using has_value_member_t
		= typename has_value_member<T>::type;

	template<class T> using copy_construction_t
		= decltype(std::declval<T>()(std::declval<T&>()));

	template<class, class = void> struct is_copy_constructible : false_type {};
	template<class T>
		struct is_copy_constructible<T, void_t<copy_construction_t<T>>>
		: true_type {};
	template<class T> using is_copy_constructible_t
		= typename is_copy_constructible<T>::type;

	template<class T> using copy_assignment_t
		= decltype(std::declval<T&>() = std::declval<T&>());
	template<class, class = void> struct is_copy_assignable : false_type {};
	template<class T> struct is_copy_assignable<T, void_t<copy_assignment_t<T>>>
		: is_same<copy_assignment_t<T>, T&> {};
	template<class T> using is_copy_assignable_t
		= typename is_copy_assignable<T>::type;

	template<class T> using move_assignment_t
		= decltype(std::declval<T&>() = std::declval<T&&>());
	template<class, class = void> struct is_move_assignable : false_type {};
	template<class T> struct is_move_assignable<T, void_t<move_assignment_t<T>>>
		: is_same<move_assignment_t<T>, T&> {};
	template<class T> using is_move_assignable_t
		= typename is_move_assignable<T>::type;

	template<class T> struct remove_const          : type_is<T> {};
	template<class T> struct remove_const<const T> : type_is<T> {};
	template<class T> using remove_const_t = typename remove_const<T>::type;

	template<class T> struct remove_volatile             : type_is<T> {};
	template<class T> struct remove_volatile<volatile T> : type_is<T> {};
	template<class T> using remove_volatile_t = typename remove_volatile<T>::type;

	template<class T> using remove_cv = remove_const<remove_volatile<T>>;
	template<class T> using remove_cv_t = typename remove_cv<T>::type;

	template<class T> using is_void = is_same<remove_cv_t<T>, void>;
	template<class T> using is_void_t = typename is_void<T>::type;

	/******************************************************************/

	template<class C, class F>
		void for_all(C &c, F f)
		{
			for (auto &e: c) {
				f(*e);
			}
		}

	template<class C, class F, class P>
		void for_some(C &c, F f, P p)
		{
			for_all(c, [f](typename C::value_type &e)
					{ if (P(*e)) { f(*e); } });
		}

	template<class C, class F, class A, class P>
		A scan(C &c, F f, A acc, P p = true)
		{
			for_some(c, [&acc,f](typename C::value_type &e)
					{
					acc = f(acc, *e);
					});
			// for (auto &e: c) {
			// 	acc = f(acc, *e);
			// }
			return acc;
		}
}

#endif /* COMMONT_H */

