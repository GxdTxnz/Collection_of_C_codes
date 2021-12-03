public class SortsTest 
{
	public static void main(String[] args) 
	{
		System.out.println("До сортировок:");
		int[] arr1 = {2, 1024, 4, 32, 256, 8, 16, 512, 32, 64, 64, 128};
		int[] arr2 = {3, 59049, 9, 9, 19683, 27, 6561, 6561, 81, 2187, 243, 729};
		int[] arr3 = {4, 1048576, 16, 262144, 64, 65536, 256, 65536, 65536, 1024, 1024, 16384, 4096};
		System.out.println("-----------------------------------------");
		for (int i : arr1) 
		{
			System.out.print(i + " ");
		}
		System.out.println();
		for (int i : arr2) 
		{
			System.out.print(i + " ");
		}
		System.out.println();
		for (int i : arr3) 
		{
			System.out.print(i + " ");
		}
		System.out.println();
		System.out.println("-----------------------------------------");
		Sorts test1 = new Sorts(arr1);
		Sorts test2 = new Sorts(arr2);
		Sorts test3 = new Sorts(arr3); 
		test1.bubbleSort();
		test2.insertionSort();
		test3.selectionSort();
		System.out.println("После сортировок:");
		System.out.println("-----------------------------------------");
		System.out.println("Пузырьковая:");
		for (int j : arr1) 
		{
			System.out.print(j + " ");
		}
		System.out.println();
		System.out.println("Вставка:");
		for (int j : arr2) 
		{
			System.out.print(j + " ");
		}
		System.out.println();
		System.out.println("Выборка:");
		for (int j : arr3) 
		{
			System.out.print(j + " ");
		}
		System.out.println();
		System.out.println("-----------------------------------------");
	}
}
