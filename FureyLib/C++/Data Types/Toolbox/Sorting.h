// .h
// Static Sort Functions
// by Kyle Furey

#pragma once

/** A collection of useful collection types in C++. */
namespace Toolbox {

	// SORTING

	/** Iterator-based sorting functions for all Toolbox collections. */
	class Sorting final {
		// ABSTRACT

		/** Ensures this class cannot be instantiated. */
		virtual void Abstract() = 0;


		// SORTING

		/** Recursively splits and merges the collection until it is sorted. */
		template <typename CollectionType, typename Type>
		static void RecursiveMergeSort(CollectionType& Collection, const size_t Begin, const size_t End) {
			if (Begin >= End) {
				return;
			}
			const size_t Middle = (Begin + End) / 2;
			RecursiveMergeSort<CollectionType, Type>(Collection, Begin, Middle);
			RecursiveMergeSort<CollectionType, Type>(Collection, Middle + 1, End);
			Merge<CollectionType, Type>(Collection, Begin, Middle, End);
		}

		/** Merges the collection at the given indicies for merge sort. */
		template <typename CollectionType, typename Type>
		static void Merge(CollectionType& Collection, size_t Begin, size_t Middle, size_t End) {
			const size_t LeftSize = Middle - Begin + 1;
			Type* Left = new Type[LeftSize];
			for (size_t Index = 0; Index < LeftSize; ++Index) {
				Left[Index] = Collection[Begin + Index];
			}
			const size_t RightSize = End - Middle;
			Type* Right = new Type[RightSize];
			for (size_t Index = 0; Index < RightSize; ++Index) {
				Right[Index] = Collection[Middle + Index + 1];
			}
			Middle = Begin;
			Begin = 0;
			End = 0;
			while (Begin < LeftSize && End < RightSize) {
				if (!(Left[Begin] > Right[End])) {
					Collection[Middle] = Left[Begin];
					++Begin;
				}
				else {
					Collection[Middle] = Right[End];
					++End;
				}
				++Middle;
			}
			while (Begin < LeftSize) {
				Collection[Middle] = Left[Begin];
				++Begin;
				++Middle;
			}
			while (End < RightSize) {
				Collection[Middle] = Right[End];
				++End;
				++Middle;
			}
			delete[] Left;
			Left = nullptr;
			delete[] Right;
			Right = nullptr;
		}

		/** Recursively partitions and separates the collection until it is sorted. */
		template <typename CollectionType, typename Type>
		static void RecursiveQuickSort(CollectionType& Collection, const size_t Low, const size_t High) {
			if (Low >= High) {
				return;
			}
			const size_t PivotIndex = Partition<CollectionType, Type>(Collection, Low, High, Collection[High]);
			if (PivotIndex > 0) {
				RecursiveQuickSort<CollectionType, Type>(Collection, Low, PivotIndex - 1);
			}
			RecursiveQuickSort<CollectionType, Type>(Collection, PivotIndex + 1, High);
		}

		/** Segments the collection at the given pivot and returns the pivot's index. */
		template <typename CollectionType, typename Type>
		static size_t Partition(CollectionType& Collection, const size_t Low, const size_t High, const Type& Pivot) {
			size_t PivotIndex = Low;
			for (size_t Index = Low; Index < High; ++Index) {
				if (!(Collection[Index] > Pivot)) {
					const Type Swapped = Collection[PivotIndex];
					Collection[PivotIndex] = Collection[Index];
					Collection[Index] = Swapped;
					++PivotIndex;
				}
			}
			const Type Swapped = Collection[PivotIndex];
			Collection[PivotIndex] = Collection[High];
			Collection[High] = Swapped;
			return PivotIndex;
		}

	public:

		// SORTING

		/** Returns whether the collection is sorted using the collection Type's > operator. */
		template <typename CollectionType, typename Type>
		static bool IsSorted(const size_t Size, const CollectionType& Collection) {
			for (size_t Index = 0; Index < Size - 1; ++Index) {
				if (Collection[Index] > Collection[Index + 1]) {
					return false;
				}
			}
			return true;
		}

		/** Bubble sorts the collection using the collection Type's > operator. */
		template <typename CollectionType, typename Type>
		static void BubbleSort(const size_t Size, CollectionType& Collection) {
			for (size_t Left = 0; Left < Size - 1; ++Left) {
				bool HasSwapped = false;
				for (size_t Right = 0; Right < Size - Left - 1; ++Right) {
					if (Collection[Right] > Collection[Right + 1]) {
						const Type Swapped = Collection[Right];
						Collection[Right] = Collection[Right + 1];
						Collection[Right + 1] = Swapped;
						HasSwapped = true;
					}
				}
				if (!HasSwapped) {
					return;
				}
			}
		}

		/** Merge sorts the collection using the collection Type's > operator. */
		template <typename CollectionType, typename Type>
		static void MergeSort(const size_t Size, CollectionType& Collection) {
			RecursiveMergeSort<CollectionType, Type>(Collection, 0, Size - 1);
		}

		/** Quick sorts the collection using the collection Type's > operator. */
		template <typename CollectionType, typename Type>
		static void QuickSort(const size_t Size, CollectionType& Collection) {
			RecursiveQuickSort<CollectionType, Type>(Collection, 0, Size - 1);
		}
	};
}
